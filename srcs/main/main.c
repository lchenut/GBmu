#include <stdio.h>
#include <strings.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_surface.h"
#include "memory.h"
#include "registers.h"
#include "opcodes.h"
#include "prog.h"

t_registers	reg;
t_memory	mem;
t_vector	*rom;
SDL_Window	*win;
SDL_Renderer	*renderer;
TTF_Font	*font;

int			main(int ac, char **av)
{
	t_prog	*prog;

	prog = prog_new(ac, av);
	if (prog->error) {
		dprintf(2, "%s\n", prog->error);
		return (1);
	}
	prog_loop(prog);
	prog_del(prog);
	return (0);
}
