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

	uint16_t addr = opcode & 0x0FFF; // nnn/addr: lowest 12b of the instruction    
	uint8_t n = opcode & 0x000F; // n/nibble: lowest 4b of the instruction
	uint8_t kk = opcode & 0x00FF; // kk/byte: lowest 8b of the instruction
	uint8_t x = (opcode & 0x0F00) >> 8; // x: lower 4b of the high byte
	uint8_t y = (opcode & 0x00F0) >> 4; // y: upper 4b of the low byte

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
			chip->PC = addr; 	
			break;
		case 0x2000: // 2nnn -> CALL addr
			chip->stack[chip->SP] = chip->PC;
			chip->SP++;
			chip->PC = addr;
			break;
		case 0x3000: {// 3xkk -> SE Vx, byte
			uint8_t vx = chip->V[x];
			if (vx == kk) chip->PC += 2;
			
			break;
		}
		case 0x4000: { // 4xkk -> SNE Vx, byte
			uint8_t vx = chip->V[x];
			if (vx != kk) chip->PC += 2;

			break;
		}
		case 0x5000: { // 5xy0 -> SE Vx, Vy
			uint8_t vx = chip->V[x];
			uint8_t vy = chip->V[y];
			if(vx == vy) chip->PC += 2;

			break;
		}
		case 0x6000: // 6xkk -> LD Vx, byte
			chip->V[x] = kk;
			break;
		case 0x7000: // 7xkk -> ADD Vx, byte
			chip->V[x] += kk;
			break;
		case 0x8000:
			switch(opcode & 0x000F) {
				case 0x0000: // LD Vx, Vy
					chip->V[x] = chip->V[y];
					break;
				case 0x0001: // OR Vx, Vy
					chip->V[x] |= chip->V[y];
					break;
				case 0x0002: // AND Vx, Vy
					chip->V[x] &= chip->V[y];
					break;
				case 0x0003: // XOR Vx, Vy
					chip->V[x] ^= chip->V[y];
					break;
				case 0x0004: { // ADD Vx, Vy

					// TODO: FAZER O MECANISMO DE CARRY
					//chip->V[x] += chip->V[y];
					if (chip->V[vx_i] & 0x
							 // Como verificar se o resultado deu +8 bits?

					break;
				}
				case 0x0005:
			}
			
			break;
		case 0x9000: { // 9xy0 -> SNE Vx, Vy
			uint8_t vx = chip->V[x];
			uint8_t vy = chip->V[y];
			if (vx != vy) chip->PC += 2;
			
			break;
		}
		case 0xA000: // Annn -> LD I, addr
			chip->I = addr;
			break;
		case 0xB000: // Bnnn -> JP V0, addr
			chip->PC = addr + chip->V[0];
			break;
		case 0xC000:
			
		case 0xD000:

		case 0xE000:

		case 0xF000:
	}
}
