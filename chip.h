#ifndef CHIP_H
#define CHIP_H

#include <stdint.h>

#define MEM_SIZE 4096

#define DISPLAY_ROWS 32
#define DISPLAY_COLS 64

typedef struct {
	uint16_t I;
	uint16_t PC;
	uint8_t SP;

	uint8_t V[16];

	uint8_t delay_timer;
	uint8_t sound_timer;

	uint8_t memory[MEM_SIZE];

	uint8_t display[DISPLAY_ROWS][DISPLAY_COLS];
} Chip;

Chip *initialize();

#endif
