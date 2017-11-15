#include "prog.h"
t_debugger	*debugger;

unsigned char	game[160][144][3];

static void		update_divider_timer(void)
{
	static size_t	inner_divider_timer = 0;

	inner_divider_timer += last_clock;
	if (inner_divider_timer >= 256) {
		Div_Register += 1;
		inner_divider_timer -= 256;
	}
}

static size_t	get_clock_frequency(void)
{
	switch (Timer_Control & 3) {
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
	if ((Timer_Control >> 2) & 1) {
		inner_timer += last_clock;
		if (inner_timer >= get_clock_frequency()) {
			if (Timer_Counter == 0xff) {
				Timer_Counter = Timer_Modulo;
				Interrupt_Flag |= (1 << 2);
			} else {
				Timer_Counter += 1;
			}
			inner_timer = 0;
		}
	}
}

static void		interrupt(unsigned char c)
{
	master_interrupt = false;
	memory_push_word_on_stack(reg.pc);
	Interrupt_Flag &= ~(1 << c);
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
			if ((Interrupt_Flag >> c) & 1) {
				if ((Interrupt_Enable >> c) & 1) {
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
	if (LCD_Y_Coord >= 144) {
		mode = 1;
		should_interrupt = (((LCD_Status >> 4) & 1) != 0);
	} else if (scanline_counter < 80) {
		mode = 2;
		should_interrupt = (((LCD_Status >> 5) & 1) != 0);
	} else if (scanline_counter < 252) {
		mode = 3;
	} else {
		mode = 0;
		should_interrupt = (((LCD_Status >> 3) & 1) != 0);
	}
	if (should_interrupt && mode != (LCD_Status & 0x3)) {
		// new mode <=> interrupt
		Interrupt_Flag |= (1 << 1); // LCD Interrupt
	}
	if (LCD_Y_Coord == LCD_Y_Compare) {
		// check coincidence flag
		LCD_Status |= (1 << 2);
		if ((LCD_Status >> 6) & 1) {
			Interrupt_Flag |= (1 << 1); // LCD Interrupt
		}
	} else {
		LCD_Status &= ~(1 << 2);
	}
	LCD_Status = (LCD_Status & ~0x3) | mode;
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

	using_window = ((LCD_Control >> 5) & 1) && Window_Y_Pos <= LCD_Y_Coord;
	if ((LCD_Control >> 4) & 1) {
		tile_data = 0x8000;
		unsig = true;
	} else {
		tile_data = 0x8800;
		unsig = false;
	}
	if ((using_window && (LCD_Control >> 6) & 1) || (!using_window && (LCD_Control >> 3) & 1)) {
		bg_memory_address = 0x9c00;
	} else {
		bg_memory_address = 0x9800;
	}
	if (using_window) {
		posy = LCD_Y_Coord - Window_Y_Pos;
	} else {
		posy = LCD_Y_Coord + Scroll_Y;
	}
	for (int pixel = 0; pixel < 160; pixel += 1) {
		posx = pixel + Scroll_X;
		if (using_window && pixel >= Window_X_Pos - 7) {
			posx = pixel - Window_X_Pos - 7;
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
		int palette = BG_Palette;
		int r, g, b;
		switch ((palette >> (color_num * 2)) & 0x3)
		{
			case 0: r = 0xff; g = 0xff; b = 0xff; break ;
			case 1: r = 0xcc; g = 0xcc; b = 0xcc; break ;
			case 2: r = 0x77; g = 0x77; b = 0x77; break ;
			case 3: r = 0x00; g = 0x00; b = 0x00; break ;
		}
		game[pixel][LCD_Y_Coord][0] = r;
		game[pixel][LCD_Y_Coord][1] = g;
		game[pixel][LCD_Y_Coord][2] = b;
	}
} 

void			render_sprites(void)
{
	unsigned char	size_y;
	unsigned char	posx;
	unsigned char	posy;
	unsigned char	tile_loc;
	unsigned char	attributes;
	unsigned char	data1;
	unsigned char	data2;
	int				line;

	size_y = (LCD_Control >> 2) & 1 ? 16 : 8;
	for (unsigned short index_sprite = 0; index_sprite < 0x100; index_sprite += 4) {
		posy = memory_read_byte(0xfe00 + index_sprite) - 16;
		posx = memory_read_byte(0xfe00 + index_sprite + 1) - 8;
		tile_loc = memory_read_byte(0xfe00 + index_sprite + 2);
		attributes = memory_read_byte(0xfe00 + index_sprite + 3);
		if (LCD_Y_Coord < posy || LCD_Y_Coord >= (posy + size_y)) {
			continue ;
		}
		if ((attributes >> 6) & 1) {
			line = 2 * (size_y - (LCD_Y_Coord - posy));
		} else {
			line = 2 * (LCD_Y_Coord - posy);
		}
		data1 = memory_read_byte(0x8000 + (tile_loc * 16) + line);
		data2 = memory_read_byte(0x8000 + (tile_loc * 16) + line + 1);
		for (int tile_pixel = 7; tile_pixel >= 0; tile_pixel -= 1) {
			int color_bit = tile_pixel;
			if ((attributes >> 5) & 1) {
				color_bit = 7 - color_bit;
			}
			int color_num = (((data2 >> color_bit) & 1) << 1) | ((data1 >> color_bit) & 1);
			int palette = BG_Palette;
			int r, g, b;
			switch ((palette >> (color_num * 2)) & 0x3)
			{
				case 0: r = 0xff; g = 0xff; b = 0xff; break ;
				case 1: r = 0xcc; g = 0xcc; b = 0xcc; break ;
				case 2: r = 0x77; g = 0x77; b = 0x77; break ;
				case 3: r = 0x00; g = 0x00; b = 0x00; break ;
			}
			game[posx + (7 - tile_pixel)][LCD_Y_Coord][0] = r;
			game[posx + (7 - tile_pixel)][LCD_Y_Coord][1] = g;
			game[posx + (7 - tile_pixel)][LCD_Y_Coord][2] = b;
		}
	}
}

static void		draw_scanline(void)
{
	if (LCD_Control & (1 << 0)) {
		render_tiles();
	}
	if (LCD_Control & (1 << 1)) {
		render_sprites();
	}
} 

static void		update_graphics(t_debugger *this)
{
	(void)(this);
	static size_t	scanline_counter = 0;

	if (((LCD_Control >> 7) & 1) == 0) {
		// if LCD is disable, reset scanline status
		scanline_counter = 0;
		LCD_Y_Coord = 0;
		LCD_Status = (LCD_Status & ~0x3) | 0x1;
		return ;
	}
	set_lcd_status(scanline_counter);
	scanline_counter += last_clock;
	if (scanline_counter > 456) {
		if (LCD_Y_Coord == 144) {
			Interrupt_Flag |= (1 << 0); // VBlank Interrupt
			//debugger_dump(this);
		} else if (LCD_Y_Coord > 153) {
			LCD_Y_Coord = 0;
		}
		if (LCD_Y_Coord < 144) {
			draw_scanline();
		}
		LCD_Y_Coord += 1;
		scanline_counter -= 456;
	}
}

static bool		find_fn(void *data, void *ctx)
{
	return (data == ctx);
}

static void		loop_debugger_next_opcode(t_debugger *this)
{
	static int	count = 0;
	next_opcode();
	update_timer();
	update_graphics(this);
	update_interrupt();
	if (total_clock >= 69905) {
		if (count++ > 100) {
			exit(0);
		}
		//debugger_print_game(this);
		//debugger_dump(this);
		total_clock -= 69905;
	}
	(void)this;
}

//static void		loop_debugger_keyboard_type(t_prog *this, t_debugger *debugger, SDL_Event *event)
//{
//	if (event->key.keysym.scancode == SDL_SCANCODE_SPACE) {
//		debugger->step_by_step = !debugger->step_by_step;
//		if (debugger->step_by_step == true) {
//			debugger_dump(debugger);
//		}
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_RETURN) {
//		if (debugger->step_by_step == true) {
//			loop_debugger_next_opcode(debugger);
//			debugger_dump(debugger);
//		}
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_END) {
//		debugger_scroll_end(debugger);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_HOME) {
//		debugger_scroll_home(debugger);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_Q) {
//		joypad &= ~(1 << 7);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_W) {
//		joypad &= ~(1 << 6);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_B) {
//		joypad &= ~(1 << 5);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_A) {
//		joypad &= ~(1 << 4);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_DOWN) {
//		joypad &= ~(1 << 3);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_UP) {
//		joypad &= ~(1 << 2);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_LEFT) {
//		joypad &= ~(1 << 1);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT) {
//		joypad &= ~(1 << 0);
//	}
//	if (!debugger->step_by_step) {
//		loop_debugger_next_opcode(debugger);
//		//if (vector_exists(debugger->breakpoints, find_fn, (void *)((size_t)reg.pc))) {
//		//	debugger->step_by_step = true;
//		//	debugger_dump(debugger);
//		//}
//	}
//	(void)this;
//}
//
//static void		loop_debugger_keyboard_up_type(t_prog *this, t_debugger *debugger, SDL_Event *event)
//{
//	if (event->key.keysym.scancode == SDL_SCANCODE_Q) {
//		joypad |= (1 << 7);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_W) {
//		joypad |= (1 << 6);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_B) {
//		joypad |= (1 << 5);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_A) {
//		joypad |= (1 << 4);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_DOWN) {
//		joypad |= (1 << 3);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_UP) {
//		joypad |= (1 << 2);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_LEFT) {
//		joypad |= (1 << 1);
//	} else if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT) {
//		joypad |= (1 << 0);
//	}
//	(void)this;
//	(void)debugger;
//}
//
//static void		loop_debugger_mouse_type(t_prog *this, t_debugger *debugger, SDL_Event *event)
//{
//	if (scroll_click(debugger->scroll_xxd, event->button.x, event->button.y)) {
//		debugger_dump(debugger);
//	} else if (debugger->step_by_step && debugger_add_breakpoint(debugger, event->button.x, event->button.y)) {
//		debugger_dump(debugger);
//	}
//	(void)this;
//}

static void		loop_debugger(t_prog *this)
{
	(void)find_fn;
	(void)this;
//	SDL_Event	event;
//	t_debugger	*debugger;
//	(void)loop_debugger_keyboard_type;
//	(void)loop_debugger_mouse_type;
//	(void)this;
//	(void)event;
//	(void)find_fn;

	debugger = debugger_new();
	//debugger_dump(debugger);
	//debugger->step_by_step = true;
	debugger->step_by_step = false;
//	SDL_WaitEvent(&event);
	while (1) {
//		while (SDL_PollEvent(&event)) {
//			if (event.type == SDL_QUIT) {
//				return ;
//			} else if (event.type == SDL_KEYDOWN) {
//				loop_debugger_keyboard_type(this, debugger, &event);
//			} else if (event.type == SDL_KEYUP) {
//				loop_debugger_keyboard_up_type(this, debugger, &event);
//			} else if (event.type == SDL_MOUSEBUTTONDOWN) {
//				loop_debugger_mouse_type(this, debugger, &event);
//			}
//		}
//		if (!debugger->step_by_step) {
			loop_debugger_next_opcode(debugger);
			//if (vector_exists(debugger->breakpoints, find_fn, (void *)((size_t)reg.pc))) {
			//	debugger->step_by_step = true;
			//	debugger_dump(debugger);
			//}
//		}
	}
}

void			prog_loop(t_prog *this)
{
//	memory_to_commands();
	this->debug_mode = true;
	if (this->debug_mode == true) {
		loop_debugger(this);
	}
}
