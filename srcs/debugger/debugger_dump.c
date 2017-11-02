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
//	if (reg.pc >= index && reg.pc < index + 16) {
//		SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 0);
//		int start = (7 + (reg.pc % 16) * 2 + (reg.pc % 16) / 2) * (tw / 46);
//		int end = start + (tw / 23);
//		SDL_RenderDrawLine(this->renderer, start, *h + th, end, *h + th);
//		SDL_RenderDrawLine(this->renderer, start, *h + th - 1, end, *h + th - 1);
//	}
	SDL_Rect dstrect = { 10, *h + 10, tw, th };
	SDL_RenderCopy(this->renderer, text, NULL, &dstrect);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(surf);
	free(line);
	*h += th;
	*w = tw;
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

t_scroll          *scroll_new(size_t total, size_t size, size_t posx, size_t posy, size_t width, size_t height)
{
	t_scroll        *this;

	this = malloc(sizeof(t_scroll));
	this->total = total;
	this->size = size;
	this->posx = posx;
	this->posy = posy;
	this->height = height;
	this->width = width;
	this->current = 0;
	return (this);
}

void              scroll_del(t_scroll *this)
{
	if (!this) {
		return ;
	}
	free(this);
}

static void           draw_rectangle(SDL_Renderer *renderer, size_t x, size_t y, size_t w, size_t h)
{
	SDL_Rect        rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_RenderDrawRect(renderer, &rect);
}

static void           fill_rectangle(SDL_Renderer *renderer, size_t x, size_t y, size_t w, size_t h)
{
	SDL_Rect        rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_RenderFillRect(renderer, &rect);
}

void              scroll_draw(t_scroll *this, SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 167, 167, 167, 0);
	draw_rectangle(renderer, this->posx, this->posy, this->width, this->height);
	draw_rectangle(renderer, this->posx + 1, this->posy + 1, this->width - 2, this->height - 2);
	SDL_SetRenderDrawColor(renderer, 230, 230, 230, 0);
	fill_rectangle(renderer, this->posx + 2, this->posy + 2, this->width - 4, this->height - 4);
	SDL_SetRenderDrawColor(renderer, 120, 120, 120, 0);
	fill_rectangle(renderer, this->posx + 1, this->posy + 1, this->width - 2, this->width - 1);
	fill_rectangle(renderer, this->posx + 1, this->posy + this->height - this->width, this->width - 2, this->width - 1);
	fill_rectangle(renderer, this->posx + 2,
			this->posy + this->width + (this->current * (this->height - this->width * 2)) / this->total,
			this->width - 4, this->size * (this->height - this->width * 2) / this->total + 1);
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0);
	draw_rectangle(renderer, this->posx + 2,
			this->posy + this->width + (this->current * (this->height - this->width * 2)) / this->total,
			this->width - 4, this->size * (this->height - this->width * 2) / this->total + 1);
}

bool		scroll_click(t_scroll *this, size_t x, size_t y)
{
	if (x >= this->posx && x <= this->posx + this->width) {
		if (y >= this->posy && y <= this->posy + this->width) {
			if (this->current > 0) {
				this->current -= 1;
				return (true);
			}
		} else if (y >= this->posy + this->height - this->width &&
				y <= this->posy + this->height) {
			if (this->current + 1 < this->total - this->size) {
				this->current += 1;
				return (true);
			}
		} else if (y > this->posy + this->width && y <= this->posy + this->width + (this->current * (this->height - this->width * 2)) / this->total) {
			if (this->current < this->size && this->current) {
				this->current = 0;
				return (true);
			} else if (this->current) {
				this->current -= this->size;
				return (true);
			}
		} else if (y > this->posy + this->width + (this->current + this->size) * (this->height - this->width * 2) / this->total &&
				y < this->posy + this->height - this->width) {
			if (this->current + 2 * this->size < this->total) {
				this->current += this->size;
				return (true);
			} else if (this->current + 2 * this->size >= this->total) {
				this->current = this->total - this->size - 1;
				return (true);
			}
		}
	}
	return (false);
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
	SDL_RenderClear(this->renderer);
	for (; i <= e; i += 16) {
		draw_line(this, i, &w, &h);
	}
	scroll_draw(this->scroll_xxd, this->renderer);
	dump_registers(this);
	SDL_RenderPresent(this->renderer);
}
