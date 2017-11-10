#include "prog.h"
#include "debugger.h"
#include "opcodes.h"

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

static bool		find_fn(void *data, void *ctx)
{
	return (data == ctx);
}

static void	dump_command(t_debugger *this, const t_opcode *op, unsigned short index, int command_num)
{
	SDL_Surface *surf;
	SDL_Texture *text;
	char		*line;
	SDL_Color	wh = { 0, 0, 0, 255 };
	SDL_Color	re = { 255, 0, 0, 255 };
	int			tw = 0;
	int			th = 0;

	if (op->argument == 0) {
		asprintf(&line, "%04hx:  %s", index, op->name);
	} else if (op->argument == 1) {
		asprintf(&line, "%04hx:  %s  {0x%02hhx}", index, op->name, memory_read_byte(index + 1));
	} else {
		asprintf(&line, "%04hx:  %s  {0x%04hx}", index, op->name, memory_read_word(index + 1));
	}
	if (vector_exists(this->breakpoints, find_fn, (void *)((size_t)index))) {
		surf = TTF_RenderText_Solid(this->font, line, re);
	} else {
		surf = TTF_RenderText_Solid(this->font, line, wh);
	}
	text = SDL_CreateTextureFromSurface(this->renderer, surf);
	SDL_QueryTexture(text, NULL, NULL, &tw, &th);
	SDL_Rect dstrect = { 400, 100 + 10 * command_num, tw, th };
	SDL_RenderCopy(this->renderer, text, NULL, &dstrect);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(surf);
	free(line);
}

void		dump_commands(t_debugger *this)
{
	unsigned short	index;
	const t_opcode	*op;

	index = reg.pc;
	for (int i = 0; i < 10; i += 1) {
		op = get_opcode(index);
		dump_command(this, op, index, i);
		index += 1 + op->argument;
	}
}

void		debugger_print_game(t_debugger *this)
{
	for (unsigned char i = 0; i < 160; i += 1) {
		for (unsigned char j = 0; j < 144; j += 1) {
			SDL_SetRenderDrawColor(this->renderer, game[i][j][0], game[i][j][1], game[i][j][2], 0);
			SDL_RenderDrawPoint(this->renderer, 500 + i, 700 + j);
		}
	}
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
	SDL_SetRenderDrawColor(this->renderer, 127, 127, 127, 255);
	SDL_RenderClear(this->renderer);
	//SDL_RenderPresent(this->renderer);
	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
	visual_fill_rectangle(this->renderer, 8, 8, 330, 1137);
	visual_fill_rectangle(this->renderer, 398, 8, 109, 67);
	visual_fill_rectangle(this->renderer, 398, 98, 200, 117);
	//SDL_RenderClear(this->renderer);
	for (; i <= e; i += 16) {
		draw_line(this, i, &w, &h);
	}
	scroll_draw(this->scroll_xxd, this->renderer);
	dump_registers(this);
	dump_commands(this);
	debugger_print_game(this);
	SDL_RenderPresent(this->renderer);
//	for (unsigned char i = 0; i < 144; i += 1) {
//		printf("game[0][%hhu] = { %hhu %hhu %hhu }\n", i, game[0][i][0], game[0][i][1], game[0][i][2]);
//	}
}

void			bp_add_if_exists_remove_else(t_debugger *this, unsigned short bp)
{
	if (vector_exists(this->breakpoints, find_fn, (void *)((size_t)bp))) {
		vector_find_pop(this->breakpoints, find_fn, (void *)((size_t)bp));
	} else {
		vector_push_back(this->breakpoints, (void *)((size_t)bp));
	}
}

bool			debugger_add_breakpoint(t_debugger *this, size_t x, size_t y)
{
	unsigned short	index;
	const t_opcode	*op;

	if (x > 400 && x < 600 && y > 100 && y < 205) {
		index = reg.pc;
		for (y = (y - 100) / 10; y > 0; y -= 1) {
			op = get_opcode(index);
			index += 1 + op->argument;
		}
		bp_add_if_exists_remove_else(this, index);
		return (true);
	}
	return (false);
}
