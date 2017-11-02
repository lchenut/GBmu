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
	if (reg.pc >= index && reg.pc < index + 16) {
		SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 0);
		int start = (7 + (reg.pc % 16) * 2 + (reg.pc % 16) / 2) * (tw / 46);
		int end = start + (tw / 23);
		SDL_RenderDrawLine(this->renderer, start, *h + th, end, *h + th);
		SDL_RenderDrawLine(this->renderer, start, *h + th - 1, end, *h + th - 1);
	}
	SDL_Rect dstrect = { 0, *h, tw, th };
	SDL_RenderCopy(this->renderer, text, NULL, &dstrect);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(surf);
	free(line);
	*h += th;
	(void)w;
}

void		dump_registers(t_debugger *this)
{
	SDL_Surface *surf;
	SDL_Texture *text;
	char		*line;
	SDL_Color	wh = { 0, 0, 0, 255 };
	int			tw = 0;
	int			th = 0;

	asprintf(&line, "af:  %04hx   bc:  %04hx   de:  %04hx   hl:  %04hx   pc:  %04hx    sp:  %04hx",
			reg.af, reg.bc, reg.de, reg.hl, reg.pc, reg.sp);
	surf = TTF_RenderText_Solid(this->font, line, wh);
	text = SDL_CreateTextureFromSurface(this->renderer, surf);
	SDL_QueryTexture(text, NULL, NULL, &tw, &th);
	SDL_Rect dstrect = { 100, 1200, tw, th };
	SDL_RenderCopy(this->renderer, text, NULL, &dstrect);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(surf);
	free(line);
}

void		debugger_dump(t_debugger *this)
{
	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
	SDL_RenderClear(this->renderer);
	for (int i = 0, w = 0, h = 0; i < 0x501; i += 16) {
		draw_line(this, i, &w, &h);
	}
	dump_registers(this);
	SDL_RenderPresent(this->renderer);
}
