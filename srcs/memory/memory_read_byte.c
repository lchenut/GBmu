#include "memory.h"

unsigned char	joypad = 0xff;

unsigned char	memory_read_byte(unsigned short address)
{
	if (address == 0xff00) {
		unsigned char	jp = mem.memory[address],l;

		jp = jp ^ 0xff;
		if ((mem.memory[address] >> 5) & 1) {
			l = jp & ((joypad & 0x0f) | 0xf0);
			return (jp & ((joypad & 0x0f) | 0xf0));
		} else if ((mem.memory[address] >> 4) & 1) {
			l = jp & ((joypad >> 4) | 0xf0);
			return (jp & ((joypad >> 4) | 0xf0));
		}
	}
	return (mem.memory[address]);
}
