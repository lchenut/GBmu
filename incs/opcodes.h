#ifndef OPCODES_H
# define OPCODES_H

# include "basics.h"

typedef struct	s_opcode {
	char		*name;
	size_t		argument;
	void		*fn;
	size_t		clock;
}				t_opcode;

extern size_t	total_clock;
extern size_t	last_clock;

extern bool		master_interrupt;

void			next_opcode(void);

const t_opcode	*get_opcode(unsigned short index);

#endif // OPCODES_H
