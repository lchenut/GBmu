#include "prog.h"

void			prog_del(t_prog *this)
{
	if (!this) {
		return ;
	}
	if (this->fd > 0) {
		close(this->fd);
	}
	if (this->error) {
		free(this->error);
	}
//	SDL_Quit();
//	TTF_Quit();
	free(this);
}
