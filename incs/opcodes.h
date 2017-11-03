#ifndef OPCODES_H
# define OPCODES_H

# include "basics.h"

extern size_t	total_clock;
extern size_t	last_clock;

extern bool		master_interrupt;

void			next_opcode(void);

#endif // OPCODES_H
