#include "memory.h"

unsigned char	memory_read_byte(unsigned short address)
{
	if (address == 0xff00) {
		if ((mem.memory[address] >> 5) & 1) {
			return (0xef); // TODO
		} else if ((mem.memory[address] >> 4) & 1) {
			return (0xdf); // TODO
		}
	}
	return (mem.memory[address]);
}
