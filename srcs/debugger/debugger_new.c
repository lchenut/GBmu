#include "debugger.h"

t_debugger		*debugger_new(void)
{
	t_debugger	*this;

	this = malloc(sizeof(t_debugger));
	this->window = SDL_CreateWindow("Debug", 0, 0, 2560, 1315, SDL_WINDOW_SHOWN);
	if (this->window == NULL) {
		dprintf(2 ,"Fail to init window (%s)\n", SDL_GetError());
		exit(1);
	}
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC);
	if (TTF_Init() == -1) {
		dprintf(2 ,"Fail to init TTF (%s)\n", SDL_GetError());
		exit(1);
	}
	this->font = TTF_OpenFont("/Library/Fonts/Courier New.ttf", 12);
	this->scroll_xxd = scroll_new(4096, 80, 350, 10, 20, 1133);
	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
	SDL_RenderClear(this->renderer);
	SDL_RenderPresent(this->renderer);
	return (this);
}
