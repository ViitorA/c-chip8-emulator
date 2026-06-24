#ifndef CHIP_H
#define CHIP_H

#include <stdint.h>

#define MEM_SIZE 4096
#define STACK_SIZE 16

#define DISPLAY_ROWS 32
#define DISPLAY_COLS 64

#define ADDR_MASK 0x0FFF
#define X_MASK    0x0F00
#define Y_MASK    0x00F0
#define KK_MASK   0x00FF

typedef struct {
	uint16_t I;
	uint16_t PC;
	uint8_t SP;

	uint8_t V[16];

	uint8_t delay_timer;
	uint8_t sound_timer;

	uint8_t memory[MEM_SIZE];
	uint16_t stack[STACK_SIZE];

	uint8_t display[DISPLAY_ROWS][DISPLAY_COLS];
} Chip;

Chip *initialize();
void cycle(Chip *chip);

#endif
