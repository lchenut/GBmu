#include "memory.h"

void			memory_write_byte(unsigned short address, unsigned char op)
{
	if (address < 0x8000) {
		// TODO
	} else if (address >= 0xe000 && address < 0xfe00) {
		mem.memory[address - 0x2000] = op;
	} else if (address >= 0xfea0 && address < 0xff00) {
		// restricted
	} else if (address == 0xff04) { // Divider Register (Writing any value sets it to $00)
		mem.memory[address] = 0;
	} else if (address == 0xff44) { // LCDC Y-Coordinate (Writing any value sets it to $00)
		mem.memory[address] = 0;
	} else if (address == 0xff46) {
		for (unsigned short addr = op << 8, i = 0; i < 0xa0; i += 1) {
			memory_write_byte(0xffe0 + i, memory_read_byte(addr + i));
		}
	} else if (address > 0xff4b && address < 0xff80) {
		// restricted
	} else {
		mem.memory[address] = op;
	}
}
