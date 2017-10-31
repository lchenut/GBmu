#include "registers.h"
#include <strings.h>

void			registers_reset(void)
{
	bzero(&reg, sizeof(t_registers));
	reg.af = 0x01b0;
	reg.bc = 0x0013;
	reg.de = 0x00d8;
	reg.hl = 0x014d;
	reg.sp = 0xfffe;
	reg.pc = 0x0100;
}
