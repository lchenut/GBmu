#include "memory.h"

unsigned char	memory_read_byte(unsigned short address)
{
	return (mem.memory[address]);
}
