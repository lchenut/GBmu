#include "memory.h"

void			memory_write_word(unsigned short address, unsigned short op)
{
	memory_write_byte(address, (unsigned char)(op & 0xFF));
	memory_write_byte(address + 1, (unsigned char)((op >> 8) & 0xFF));
}
