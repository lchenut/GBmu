#include "memory.h"
#include "registers.h"

unsigned char	memory_pop_byte_from_stack(void)
{
	unsigned char	ret;

	ret = mem.memory[reg.sp];
	reg.sp += 1;
	return (ret);
}

unsigned short	memory_pop_word_from_stack(void)
{
	unsigned short	ret;

	ret = *((unsigned short *)(mem.memory + reg.sp));
	reg.sp += 2;
	return (ret);
}

void			memory_push_byte_on_stack(unsigned char op)
{
	mem.memory[reg.sp] = op;
	reg.sp -= 1;
}

void			memory_push_word_on_stack(unsigned short op)
{
	*((unsigned short *)(mem.memory + reg.sp)) = op;
	reg.sp -= 2;
}
