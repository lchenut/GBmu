#ifndef SCROLL_H
# define SCROLL_H

# include "basics.h"
# include "visual.h"

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

#endif // SCROLL_H
