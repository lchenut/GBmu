#include "prog.h"

static void		loop_debugger_next_opcode(t_debugger *this)
{
	next_opcode();
	// update_timer(last_opcode_timer);
	// update_graphics(last_opcode_timer);
	// interrupt_treat();
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
	if (debugger->step_by_step) {
		if (scroll_click(debugger->scroll_xxd, event->button.x, event->button.y)) {
			debugger_dump(debugger);
		}
	}
	(void)this;
}

static void		loop_debugger(t_prog *this)
{
	SDL_Event	event;
	t_debugger	*debugger;

	debugger = debugger_new();
	debugger_dump(debugger);
	debugger->step_by_step = true;
	while (1) {
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
