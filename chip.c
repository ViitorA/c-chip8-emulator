#include "chip.h"

#include <stdlib.h>

Chip *initialize() {
	Chip *chip = (Chip*) malloc(sizeof(Chip));
	if(chip == NULL) return NULL;

	chip->I = 0;
	chip->SP = 0;
	chip->PC = 0x200;
	
	for (int i = 0; i < 16; i++) {
		chip->V[i] = 0;
		chip->stack[i] = 0;
	}

	chip->delay_timer = 0;
	chip->sound_timer = 0;

	for (int i = 0; i < MEM_SIZE; i++) {
		chip->memory[i] = 0;
	}

	for(int i = 0; i < DISPLAY_ROWS; i++) {
		for(int j = 0; j < DISPLAY_COLS; j++) {
			chip->display[i][j] = 0;
		}
	}

	return chip;
}

void cycle(Chip *chip) {
	// Fetch
	uint16_t opcode = (chip->memory[chip->PC] << 8) | (chip->memory[(chip->PC) + 1]);
	chip->PC += 2;

	/* nnn(or addr): lowest 12 bits of the instruction
	 * n(or nibble): lowest 4 bits of the instruction
	 * x: lower 4 bits of the high byte 
	 * y: upper 4 bits of the low byte
	 * kk(or byte): lowest 8 bits of the instruction
	 */

	// Execute
	switch(opcode & 0xF000) {
		case 0x0000:
			if (opcode == 0x00E0) { // CLS -> clear display
				// TODO
			} else if(opcode == 0x00EE) { // RET -> return from subroutine
				chip->SP--;
				chip->PC = chip->stack[chip->SP];
			}
			break;
		case 0x1000: // 1nnn -> JUMP addr
			chip->PC = opcode & ADDR_MASK; 	
			break;
		case 0x2000: // 2nnn -> CALL addr
			chip->stack[chip->SP] = chip->PC;
			chip->SP++;
			chip->PC = opcode & ADDR_MASK;
			break;
		case 0x3000: {// 3xkk -> SE Vx, byte
			int vx_i = (opcode & X_MASK) >> 8;
			uint8_t vx = chip->V[vx_i];
			
			uint8_t kk = opcode & KK_MASK;
			
			if (vx == kk) chip->PC += 2;
			
			break;
		}
		case 0x4000: { // 4xkk -> SNE Vx, byte
			int vx_i = (opcode & X_MASK) >> 8;
			uint8_t vx = chip->V[vx_i];

			uint8_t kk = opcode & KK_MASK;

			if (vx != kk) chip->PC += 2;

			break;
		}
		case 0x5000: { // 5xy0 -> SE Vx, Vy
			int vx_i = (opcode & X_MASK) >> 8;
			int vy_i = (opcode & Y_MASK) >> 4;

			uint8_t vx = chip->V[vx_i];
			uint8_t vy = chip->V[vy_i];

			if(vx == vy) chip->PC += 2;

			break;
		}
		case 0x6000: { // 6xkk -> LD Vx, byte
			uint8_t vx_i = (opcode & X_MASK) >> 8;
			uint8_t kk = opcode & KK_MASK;
			
			chip->V[vx_i] = kk;
			
			break;
		}
		case 0x7000: { // 7xkk -> ADD Vx, byte
			uint8_t vx_i = (opcode & X_MASK) >> 8;
			uint8_t kk = opcode & KK_MASK;

			chip->V[vx_i] += kk;

			break;
		}
		case 0x8000:

		case 0x9000:

		case 0xA000:

		case 0xB000:

		case 0xC000:

		case 0xD000:

		case 0xE000:

		case 0xF000:
	}
}
