#include "scroll.h"

void              scroll_draw(t_scroll *this, SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 167, 167, 167, 0);
	visual_draw_rectangle(renderer, this->posx, this->posy, this->width, this->height);
	visual_draw_rectangle(renderer, this->posx + 1, this->posy + 1, this->width - 2, this->height - 2);
	SDL_SetRenderDrawColor(renderer, 230, 230, 230, 0);
	visual_fill_rectangle(renderer, this->posx + 2, this->posy + 2, this->width - 4, this->height - 4);
	SDL_SetRenderDrawColor(renderer, 120, 120, 120, 0);
	visual_fill_rectangle(renderer, this->posx + 1, this->posy + 1, this->width - 2, this->width - 1);
	visual_fill_rectangle(renderer, this->posx + 1, this->posy + this->height - this->width, this->width - 2, this->width - 1);
	visual_fill_rectangle(renderer, this->posx + 2,
			this->posy + this->width + (this->current * (this->height - this->width * 2)) / this->total,
			this->width - 4, this->size * (this->height - this->width * 2) / this->total + 1);
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0);
	visual_draw_rectangle(renderer, this->posx + 2,
			this->posy + this->width + (this->current * (this->height - this->width * 2)) / this->total,
			this->width - 4, this->size * (this->height - this->width * 2) / this->total + 1);
}
