#include "memory.h"

void			memory_write_byte(unsigned short address, unsigned char op)
{
	if (address < 0x8000) {
		// TODO
	} else if (address >= 0xE000 && address < 0xFE00) {
		mem.memory[address - 0x2000] = op;
	} else if (address >= 0xFEA0 && address < 0xFF00) {
		// restricted
	} else if (address == 0xFF04) { // Divider Register (Writing any value sets it to $00)
		mem.memory[address] = 0;
	} else if (address == 0xFF44) { // LCDC Y-Coordinate (Writing any value sets it to $00)
		mem.memory[address] = 0;
	} else {
		mem.memory[address] = op;
	}
}
