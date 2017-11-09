#include "memory.h"

unsigned short	memory_read_word(unsigned short address)
{
	if (address == 0xFFFF) {
		return (memory_read_byte(address));
	}
	return (*((unsigned short *)(mem.memory + address)));
}
