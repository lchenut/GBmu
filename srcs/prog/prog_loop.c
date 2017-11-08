#include "prog.h"

static void		update_divider_timer(void)
{
	static size_t	inner_divider_timer = 0;

	inner_divider_timer += last_clock;
	if (inner_divider_timer >= 256) {
		mem.memory[0xff04] += 1;
		inner_divider_timer -= 256;
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

//unsigned char	memory_push_ // TODO

void			memory_push_byte_on_stack(unsigned char op)
{
	mem.memory[reg.sp] = op;
	reg.sp -= 1;
}

void			memory_push_word_on_stack(unsigned short op)
{
	*((unsigned short *)(mem.memory + reg.sp)) = op;
	reg.sp -= 2;
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

static void		loop_debugger_next_opcode(t_debugger *this)
{
	next_opcode();
	update_timer();
	// update_graphics(last_opcode_timer);
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
	}
	(void)this;
}

static void		loop_debugger_mouse_type(t_prog *this, t_debugger *debugger, SDL_Event *event)
{
	if (scroll_click(debugger->scroll_xxd, event->button.x, event->button.y)) {
		debugger_dump(debugger);
	}
	(void)this;
}

static void		loop_debugger(t_prog *this)
{
	SDL_Event	event;
	t_debugger	*debugger;
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
			if (loop % 100 == 0) {
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
