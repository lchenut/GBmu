#include "debugger.h"

void			debugger_del(t_debugger *this)
{
	if (!this) {
		return ;
	}
//	if (this->renderer) {
//	    SDL_DestroyRenderer(this->renderer);
//	}
//	if (this->window) {
//		SDL_DestroyWindow(this->window);
//	}
//	if (this->font) {
//		TTF_CloseFont(this->font);
//	}
	if (this->scroll_xxd) {
		scroll_del(this->scroll_xxd);
	}
	free(this);
}
