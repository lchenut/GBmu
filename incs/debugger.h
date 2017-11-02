#ifndef DEBUGGER_H
# define DEBUGGER_H

# include "basics.h"
# include "SDL.h"
# include "SDL_ttf.h"
# include "registers.h"
# include "memory.h"

typedef struct		s_scroll
{
	size_t			total;			// 0x10000 elements
	size_t			size;			// 80 line print at the same time
	size_t			posx;			// x padding
	size_t			posy;			// y padding
	size_t			width;			// width
	size_t			height;			// height
	size_t			win_posx;		// see after...
	size_t			win_posy;		// see after...
	size_t			win_width;		// see after...
	size_t			win_height;		// see after...
	size_t			current;		// current cursor position
}					t_scroll;

t_scroll			*scroll_new(size_t total, size_t size, size_t posx, size_t posy, size_t width, size_t height);
void				scroll_del(t_scroll *this);

void				scroll_draw(t_scroll *this, SDL_Renderer *renderer);
bool				scroll_click(t_scroll *this, size_t x, size_t y);

typedef struct		s_debugger
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
	bool			step_by_step;
	t_scroll		*scroll_xxd;
}					t_debugger;

t_debugger			*debugger_new(void);
void				debugger_del(t_debugger *this);

void				debugger_dump(t_debugger *this);

#endif // DEBUGGER_H
