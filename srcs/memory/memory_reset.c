#include "memory.h"
#include <strings.h>

unsigned char nintendor[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xf0, 0x00, 0xf0, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0xf3, 0x00, 0xf3, 0x00,
	0x3c, 0x00, 0x3c, 0x00, 0x3c, 0x00, 0x3c, 0x00, 0x3c, 0x00, 0x3c, 0x00, 0x3c, 0x00, 0x3c, 0x00,
	0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0x00, 0xf3, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcf, 0x00, 0xcf, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x3f, 0x00, 0x3f, 0x00, 0x0f, 0x00, 0x0f, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0x0f, 0x00, 0x0f, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0xf0, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0x00, 0xf3, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0xc0, 0x00,
	0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0xff, 0x00, 0xff, 0x00,
	0xc0, 0x00, 0xc0, 0xc0, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc3, 0x00, 0xc3, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0xfc, 0x00,
	0xf3, 0x00, 0xf3, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00,
	0x3c, 0x00, 0x3c, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0x3c, 0x00, 0x3c, 0x00,
	0xf3, 0x00, 0xf3, 0x00, 0xf3, 0x00, 0xf3, 0x00, 0xf3, 0x00, 0xf3, 0x00, 0xf3, 0x00, 0xf3, 0x00,
	0xf3, 0x00, 0xf3, 0x00, 0xc3, 0x00, 0xc3, 0x00, 0xc3, 0x00, 0xc3, 0x00, 0xc3, 0x00, 0xc3, 0x00,
	0xcf, 0x00, 0xcf, 0x00, 0xcf, 0x00, 0xcf, 0x00, 0xcf, 0x00, 0xcf, 0x00, 0xcf, 0x00, 0xcf, 0x00,
	0x3c, 0x00, 0x3c, 0x00, 0x3f, 0x00, 0x3f, 0x00, 0x3c, 0x00, 0x3c, 0x00, 0x0f, 0x00, 0x0f, 0x00,
	0x3c, 0x00, 0x3c, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0xfc, 0x00,
	0xfc, 0x00, 0xfc, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00,
	0xf3, 0x00, 0xf3, 0x00, 0xf3, 0x00, 0xf3, 0x00, 0xf3, 0x00, 0xf3, 0x00, 0xf0, 0x00, 0xf0, 0x00,
	0xc3, 0x00, 0xc3, 0x00, 0xc3, 0x00, 0xc3, 0x00, 0xc3, 0x00, 0xc3, 0x00, 0xff, 0x00, 0xff, 0x00,
	0xcf, 0x00, 0xcf, 0x00, 0xcf, 0x00, 0xcf, 0x00, 0xcf, 0x00, 0xcf, 0x00, 0xc3, 0x00, 0xc3, 0x00,
	0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0xfc, 0x00, 0xfc, 0x00,
	0x3c, 0x00, 0x42, 0x00, 0xb9, 0x00, 0xa5, 0x00, 0xb9, 0x00, 0xa5, 0x00, 0x42, 0x00, 0x3c, 0x00
};

void		memory_reset(void)
{
	bzero(&mem, sizeof(t_memory));
	mem.memory[0xff05] = 0x00; // TIMA
	mem.memory[0xff06] = 0x00; // TMA
	mem.memory[0xff07] = 0x00; // TAC
	mem.memory[0xff10] = 0x80; // NR10
	mem.memory[0xff11] = 0xbf; // NR11
	mem.memory[0xff12] = 0xf3; // NR12
	mem.memory[0xff14] = 0xbf; // NR14
	mem.memory[0xff16] = 0x3f; // NR21
	mem.memory[0xff17] = 0x00; // NR22
	mem.memory[0xff19] = 0xbf; // NR24
	mem.memory[0xff1a] = 0x7f; // NR30
	mem.memory[0xff1b] = 0xff; // NR31
	mem.memory[0xff1c] = 0x9f; // NR32
	mem.memory[0xff1e] = 0xbf; // NR33
	mem.memory[0xff20] = 0xff; // NR41
	mem.memory[0xff21] = 0x00; // NR42
	mem.memory[0xff22] = 0x00; // NR43
	mem.memory[0xff23] = 0xbf; // NR30
	mem.memory[0xff24] = 0x77; // NR50
	mem.memory[0xff25] = 0xf3; // NR51
	mem.memory[0xff26] = 0xf1; // $F0-SGB ; NR52
	mem.memory[0xff40] = 0x91; // LCDC
	mem.memory[0xff42] = 0x00; // SCY
	mem.memory[0xff43] = 0x00; // SCX
	mem.memory[0xff45] = 0x00; // LYC
	mem.memory[0xff47] = 0xfc; // BGP
	mem.memory[0xff48] = 0xff; // OBP0
	mem.memory[0xff49] = 0xff; // OBP1
	mem.memory[0xff4a] = 0x00; // WY
	mem.memory[0xff4b] = 0x00; // WX
	mem.memory[0xffff] = 0x00; // IE
	memmove(mem.vram, nintendor, sizeof(nintendor));
	//memset(mem.vram, '\xff', sizeof(mem.vram));
	//memmove(mem.vram, nintendor, sizeof(nintendor));
}
