#ifndef VISUAL_H
# define VISUAL_H

# include "SDL.h"

void		visual_draw_rectangle(SDL_Renderer *renderer, size_t x, size_t y, size_t w, size_t h);
void		visual_fill_rectangle(SDL_Renderer *renderer, size_t x, size_t y, size_t w, size_t h);

#endif // VISUAL_H
