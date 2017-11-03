#include <signal.h>
#include "prog.h"

static void		fill_rom_vector(t_prog *this)
{
	char	*str;
	int		ret;

	while (1) {
		str = malloc(sizeof(char) * 0x4000);
		bzero(str, 0x4000);
		ret = read(this->fd, str, 0x4000);
		if (ret < 0) {
			this->error	= strdup("Error open");
			break ;
		}
		if (ret == 0) {
			free(str);
			break ;
		}
		vector_push_back(rom, str);
	}
	if (vector_len(rom) < 2) {
		this->error	= strdup("Error rom");
		return ;
	}
	memmove(mem.cart, vector_get_first(rom), 0x4000);
	memmove(mem.cart + 0x4000, vector_get(rom, 1), 0x4000);
}

static void		video_init(t_prog *this)
{
	if (this->error != NULL) {
		return ;
	}
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE)) {
		asprintf(&this->error, "Fail to init SDL (%s)", SDL_GetError());
		return ;
	}
	if (TTF_Init() == -1) {
		asprintf(&this->error, "Fail to init TTF (%s)", TTF_GetError());
		return ;
	}
	signal(SIGINT, SIG_DFL);
}

t_prog			*prog_new(int ac, char **av)
{
	t_prog		*this;

	this = malloc(sizeof(t_prog));
	this->fd = 0;
	this->error = NULL;
	this->debug_mode = false;
	if (ac == 1) {
		this->error	= strdup("Rom missing");
		return (this);
	}
	this->fd = open(av[1], O_RDONLY);
	if (this->fd <= 0) {
		this->error	= strdup("Error open");
		return (this);
	}
	registers_reset();
	memory_reset();
	rom = vector_new();
	fill_rom_vector(this);
	video_init(this);
	return (this);
}
