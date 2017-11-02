#ifndef DEBUGGER_H
# define DEBUGGER_H

# include "basics.h"
# include "SDL.h"
# include "SDL_ttf.h"
# include "registers.h"
# include "memory.h"

typedef struct		s_debugger
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
	bool			step_by_step;
}					t_debugger;

t_debugger			*debugger_new(void);
void				debugger_del(t_debugger *this);

void				debugger_dump(t_debugger *this);

#endif // DEBUGGER_H
