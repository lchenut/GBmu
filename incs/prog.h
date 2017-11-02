#ifndef PROG_H
# define PROG_H

# include "basics.h"
# include "registers.h"
# include "memory.h"
# include "debugger.h"
# include "opcodes.h"

typedef struct		s_prog
{
	int				fd;
	char			*error;
	bool			debug_mode;
}					t_prog;

t_prog				*prog_new(int ac, char **av);
void				prog_del(t_prog *this);

void				prog_loop(t_prog *this);

#endif // PROG_H
