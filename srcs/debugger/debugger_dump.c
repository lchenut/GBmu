#include "debugger.h"

static void	draw_line(t_debugger *this, int index, int *w, int *h)
{
	SDL_Surface *surf;
	SDL_Texture *text;
	char		*line;
	SDL_Color	wh = { 0, 0, 0, 255 };
	int			tw = 0;
	int			th = 0;

	asprintf(&line, "%04hx:  %02hhx%02hhx %02hhx%02hhx %02hhx%02hhx %02hhx"\
			"%02hhx %02hhx%02hhx %02hhx%02hhx %02hhx%02hhx %02hhx%02hhx",
			(unsigned short)index, mem.memory[index], mem.memory[index + 1],
			mem.memory[index + 2], mem.memory[index + 3], mem.memory[index + 4],
			mem.memory[index + 5], mem.memory[index + 6], mem.memory[index + 7],
			mem.memory[index + 8], mem.memory[index + 9], mem.memory[index + 10],
			mem.memory[index + 11], mem.memory[index + 12], mem.memory[index + 13],
			mem.memory[index + 14], mem.memory[index + 15]);
	surf = TTF_RenderText_Solid(this->font, line, wh);
	text = SDL_CreateTextureFromSurface(this->renderer, surf);
	SDL_QueryTexture(text, NULL, NULL, &tw, &th);
	SDL_Rect dstrect = { 10, *h + 10, tw, th };
	SDL_RenderCopy(this->renderer, text, NULL, &dstrect);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(surf);
	free(line);
	*h += th;
	*w = tw;
}

static void	dump_register(t_debugger *this, const char *reg_name, unsigned short reg_val, int reg_num)
{
	SDL_Surface *surf;
	SDL_Texture *text;
	char		*line;
	SDL_Color	wh = { 0, 0, 0, 255 };
	int			tw = 0;
	int			th = 0;

	asprintf(&line, "%s:  %04hx", reg_name, reg_val);
	surf = TTF_RenderText_Solid(this->font, line, wh);
	text = SDL_CreateTextureFromSurface(this->renderer, surf);
	SDL_QueryTexture(text, NULL, NULL, &tw, &th);
	SDL_Rect dstrect = { 400, 10 * (reg_num + 1), tw, th };
	SDL_RenderCopy(this->renderer, text, NULL, &dstrect);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(surf);
	free(line);
}

static void	dump_flag(t_debugger *this, char flag_name, bool is_up, int flag_num)
{
	SDL_Surface *surf;
	SDL_Texture *text;
	char		*line;
	SDL_Color	wh = { 0, 0, 0, 255 };
	int			tw = 0;
	int			th = 0;

	asprintf(&line, "%c [%c]", flag_name, is_up ? 'v' : ' ');
	surf = TTF_RenderText_Solid(this->font, line, wh);
	text = SDL_CreateTextureFromSurface(this->renderer, surf);
	SDL_QueryTexture(text, NULL, NULL, &tw, &th);
	SDL_Rect dstrect = { 470, 14 * (flag_num + 1), tw, th };
	SDL_RenderCopy(this->renderer, text, NULL, &dstrect);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(surf);
	free(line);
}

void		dump_registers(t_debugger *this)
{
	dump_register(this, "af", reg.af, 0);
	dump_register(this, "bc", reg.bc, 1);
	dump_register(this, "de", reg.de, 2);
	dump_register(this, "hl", reg.hl, 3);
	dump_register(this, "pc", reg.pc, 4);
	dump_register(this, "sp", reg.sp, 5);
	dump_flag(this, 'z', FLAG_ZERO, 0);
	dump_flag(this, 'n', FLAG_NEG, 1);
	dump_flag(this, 'h', FLAG_HALF, 2);
	dump_flag(this, 'c', FLAG_CARRY, 3);
}

void		debugger_dump(t_debugger *this)
{
	size_t	i;
	size_t	e;
	int		w;
	int		h;

	i = this->scroll_xxd->current * 16;
	e = i + 0x500;
	w = 0;
	h = 0;
	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
	visual_fill_rectangle(this->renderer, 8, 8, 330, 1137);
	visual_fill_rectangle(this->renderer, 398, 8, 109, 67);
	//SDL_RenderClear(this->renderer);
	for (; i <= e; i += 16) {
		draw_line(this, i, &w, &h);
	}
	scroll_draw(this->scroll_xxd, this->renderer);
	dump_registers(this);
//	dump_command(this);
	SDL_RenderPresent(this->renderer);
}
