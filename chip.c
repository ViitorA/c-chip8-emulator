#include "chip.h"

#include <stdlib.h>

Chip *initialize() {
	Chip *chip = (Chip*) malloc(sizeof(Chip));
	if(chip == NULL) return NULL;

	// TODO
	chip->

	return chip;
}

void cycle(Chip *chip) {
	// Fetch
	uint16_t opcode = chip->memory[chip->SP];
	instruction |= chip->memory[(chip->SP) + 1];
	chip->SP += 2;

	// Decode
	switch() {

	}

	// Execute
}
