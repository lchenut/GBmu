#include "memory.h"

unsigned short	memory_read_word(unsigned short address)
{
	unsigned short	ret;
	
	if (address == 0xFFFF) {
		return (memory_read_byte(address));
	}
	ret = mem.memory[address] + (mem.memory[address + 1] << 8);
	return (mem.memory[address]);
}
