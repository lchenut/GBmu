#include "prog.h"
t_debugger	*debugger;

static void		update_divider_timer(void)
{
	static size_t	inner_divider_timer = 0;

	inner_divider_timer += last_clock;
	if (inner_divider_timer >= 256) {
		mem.memory[0xff04] += 1;
		inner_divider_timer = 0;
	}
}

static size_t	get_clock_frequency(void)
{
	switch (mem.memory[0xff07] & 3) {
		case 0: return (1024);
		case 1: return (16);
		case 2: return (64);
		case 3: return (256);
	}
	return (0);
}

static void		update_timer(void)
{
	static size_t	inner_timer = 0;

	update_divider_timer();
	if ((mem.memory[0xff07] >> 2) & 1) {
		inner_timer += last_clock;
		if (inner_timer >= get_clock_frequency()) {
			if (mem.memory[0xff05] == 0xff) {
				mem.memory[0xff05] = mem.memory[0xff06];
				mem.memory[0xff0f] |= (1 << 2);
			} else {
				mem.memory[0xff05] += 1;
			}
			inner_timer = 0;
		}
	}
}

static void		interrupt(unsigned char c)
{
	master_interrupt = false;
	memory_push_word_on_stack(reg.pc);
	mem.memory[0xff0f] &= ~(1 << c);
	// HALT MAYBE...
	switch (c) {
		case 0: reg.pc = 0x40; break ; // V-Blank
		case 1: reg.pc = 0x48; break ; // LCD-State
		case 2: reg.pc = 0x50; break ; // Timer
		case 3: reg.pc = 0x60; break ; // JoyPad
	}
}

static void		update_interrupt(void)
{
	if (master_interrupt) {
		for (unsigned char c = 0; c < 4; c += 1) {
			if ((mem.memory[0xff0f] >> c) & 1) {
				if ((mem.memory[0xffff] >> c) & 1) {
					interrupt(c);
				}
			}
		}
	}
}

static void		set_lcd_status(size_t scanline_counter)
{
	unsigned char	mode;
	bool			should_interrupt;

	should_interrupt = false;
	if (mem.memory[0xff44] >= 144) {
		mode = 1;
		should_interrupt = (((0xff41 >> 4) & 1) != 0);
	} else if (scanline_counter < 80) {
		mode = 2;
		should_interrupt = (((0xff41 >> 5) & 1) != 0);
	} else if (scanline_counter < 252) {
		mode = 3;
	} else {
		mode = 0;
		should_interrupt = (((0xff41 >> 3) & 1) != 0);
	}
	if (should_interrupt && mode != (mem.memory[0xff41] & 0x3)) {
		// new mode <=> interrupt
		mem.memory[0xff0f] |= (1 << 1); // LCD Interrupt
	}
	if (mem.memory[0xff44] == mem.memory[0xff45]) {
		// check coincidence flag
		mem.memory[0xff41] |= (1 << 2);
		if ((mem.memory[0xff41] >> 6) & 1) {
			mem.memory[0xff0f] |= (1 << 1); // LCD Interrupt
		}
	} else {
		mem.memory[0xff41] &= ~(1 << 2);
	}
	mem.memory[0xff41] = (mem.memory[0xff41] & ~0x3) | mode;
}

static void		render_tiles(void)
{
	bool			using_window;
	bool			unsig;
	unsigned short	tile_data;
	unsigned short	tile_location;
	unsigned short	tile_data_address;
	unsigned short	bg_memory_address;
	unsigned char	posy;
	unsigned char	posx;
	unsigned char	data1;
	unsigned char	data2;
	// BYTE scrollY = ReadMemory(0xFF42) ;
	// BYTE scrollX = ReadMemory(0xFF43) ;
	// BYTE windowY = ReadMemory(0xFF4A) ;
	// BYTE windowX = ReadMemory(0xFF4B) - 7;

	// The window is displayable and WindowYPos must be less than or equal to 144
	using_window = ((mem.memory[0xff40] >> 5) & 1) && mem.memory[0xff4a] < 144; // /!\ modif par rapport a l'orig
	if ((mem.memory[0xff40] >> 4) & 1) {
		tile_data = 0x8000;
		unsig = true;
	} else {
		tile_data = 0x8800;
		unsig = false;
	}
	if ((using_window && (mem.memory[0xff40] >> 6) & 1) || (mem.memory[0xff40] >> 3) & 1) {
		bg_memory_address = 0x9c00;
	} else {
		bg_memory_address = 0x9800;
	}
	posy = mem.memory[0xff44] + (using_window ? mem.memory[0xff42] : -mem.memory[0xff4a]); // C'est degueu
	// WORD tileRow = (((BYTE)(yPos/8))*32) ;
	// time to start drawing the 160 horizontal pixels
	// for this scanline
	for (int pixel = 0; pixel < 160; pixel += 1) {
		posx = pixel + mem.memory[0xff43];
		if (using_window && pixel > mem.memory[0xff4b] - 7) {
			posx -= mem.memory[0xff4b] - 7;
		}
		tile_data_address = bg_memory_address + ((posy / 8) * 32) + (posx / 8);
		if (unsig) {
			tile_location = tile_data + (memory_read_byte(tile_data_address) * 16);
		} else {
			tile_location = tile_data + (((signed char)memory_read_byte(tile_data_address) + 128) * 16);
		}
		data1 = memory_read_byte(tile_location + (posy % 8) * 2);
		data2 = memory_read_byte(tile_location + (posy % 8) * 2 + 1);
		int color_bit = (posx % 8 - 7) * -1;
		int color_num = (((data2 >> color_bit) & 1) << 1) | ((data1 >> color_bit) & 1);
		int palette = mem.memory[0xff47];
		int r, g, b;
		switch ((palette >> (color_num * 2)) & 0x3)
		{
			case 0: r = 0xff; g = 0xff; b = 0xff; /* dprintf(2, "Que Du Blanc\n"); */ break ;
			case 1: r = 0xcc; g = 0xcc; b = 0xcc; dprintf(2, "Que Du Gris Clair\n"); exit(0); break ;
			case 2: r = 0x77; g = 0x77; b = 0x77; dprintf(2, "Que Du Gris Fonce\n"); exit(0); break ;
			case 3: r = 0x00; g = 0x00; b = 0x00; dprintf(2, "Que Du Noir\n"); exit(0); break ;
		}
		SDL_SetRenderDrawColor(debugger->renderer, r, g, b, 0);
		SDL_RenderDrawPoint(debugger->renderer, 400 + pixel, 400 + mem.memory[0xff44]);
//		m_ScreenData[pixel][finaly][0] = red ;
//		m_ScreenData[pixel][finaly][1] = green ;
//		m_ScreenData[pixel][finaly][2] = blue ;
	}
	//dprintf(2, "YAYYAYAYA C'etait: %hhu\n", mem.memory[0xff44]);
	SDL_RenderPresent(debugger->renderer);
} 

static void		draw_scanline(void)
{
	if (mem.memory[0xff40] & (1 << 0)) {
		render_tiles();
	}
	if (mem.memory[0xff40] & (1 << 1)) {
//		render_sprites();
	}
} 

static void		update_graphics(void)
{
	static size_t	scanline_counter = 0;

	if (((mem.memory[0xff40] >> 7) & 1) == 0) {
		// if LCD is disable, reset scanline status
		scanline_counter = 0;
		mem.memory[0xff44] = 0;
		mem.memory[0xff41] = (mem.memory[0xff41] & ~0x3) | 0x1;
		return ;
	}
	set_lcd_status(scanline_counter);
	scanline_counter += last_clock;
	if (scanline_counter > 456) {
		mem.memory[0xff44] += 1;
		//printf("\033[32m%hhu\033[m\n", mem.memory[0xff44]);
		scanline_counter = 0;
		if (mem.memory[0xff44] == 144) {
			mem.memory[0xff0f] |= (1 << 0); // VBlank Interrupt
		} else if (mem.memory[0xff44] > 153) {
			mem.memory[0xff44] = 0;
		} else {
			draw_scanline();
		}
	}
}

static bool		find_fn(void *data, void *ctx)
{
	return (data == ctx);
}

static void		loop_debugger_next_opcode(t_debugger *this)
{
	next_opcode();
	update_timer();
	update_graphics();
	update_interrupt();
	// if (clock >= 69905) {
	// 	debugger_print_game(this);
	// }
	(void)this;
}

static void		loop_debugger_keyboard_type(t_prog *this, t_debugger *debugger, SDL_Event *event)
{
	if (event->key.keysym.scancode == SDL_SCANCODE_SPACE) {
		debugger->step_by_step = !debugger->step_by_step;
		if (debugger->step_by_step == true) {
			debugger_dump(debugger);
		}
	} else if (event->key.keysym.scancode == SDL_SCANCODE_RETURN) {
		if (debugger->step_by_step == true) {
			loop_debugger_next_opcode(debugger);
			debugger_dump(debugger);
		}
	} else if (event->key.keysym.scancode == SDL_SCANCODE_END) {
		debugger_scroll_end(debugger);
	} else if (event->key.keysym.scancode == SDL_SCANCODE_HOME) {
		debugger_scroll_home(debugger);
	}
	(void)this;
}

static void		loop_debugger_mouse_type(t_prog *this, t_debugger *debugger, SDL_Event *event)
{
	if (scroll_click(debugger->scroll_xxd, event->button.x, event->button.y)) {
		debugger_dump(debugger);
	} else if (debugger->step_by_step && debugger_add_breakpoint(debugger, event->button.x, event->button.y)) {
		debugger_dump(debugger);
	}
	(void)this;
}

static void		loop_debugger(t_prog *this)
{
	SDL_Event	event;
//	t_debugger	*debugger;
	int			loop;

	debugger = debugger_new();
	debugger_dump(debugger);
	debugger->step_by_step = true;
	loop = 0;
	while (1) {
		loop += 1;
		if (!debugger->step_by_step) {
			SDL_WaitEventTimeout(&event, 0);
		} else {
			SDL_WaitEvent(&event);
		}
		if (event.type == SDL_QUIT) {
			break ;
		} else if (event.type == SDL_KEYDOWN) {
			loop_debugger_keyboard_type(this, debugger, &event);
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			loop_debugger_mouse_type(this, debugger, &event);
		} else if (!debugger->step_by_step) {
			loop_debugger_next_opcode(debugger);
			if (vector_exists(debugger->breakpoints, find_fn, (void *)((size_t)reg.pc))) {
				debugger->step_by_step = true;
				debugger_dump(debugger);
			} else if (loop % 10000 == 0) {
				debugger_dump(debugger);
				loop = 0;
			}
		}
	}
}

void			prog_loop(t_prog *this)
{
	this->debug_mode = true;
	if (this->debug_mode == true) {
		loop_debugger(this);
	}
	(void)this;
}
