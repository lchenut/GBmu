#include "prog.h"

static void		loop_debugger_keyboard_type(t_prog *this, t_debugger *debugger, SDL_Event *event)
{
	if (event->key.keysym.scancode == SDL_SCANCODE_SPACE) {
		debugger->step_by_step = !debugger->step_by_step;
		if (debugger->step_by_step == true) {
			debugger_dump(debugger);
		}
	} else if (event->key.keysym.scancode == SDL_SCANCODE_RETURN) {
		if (debugger->step_by_step == true) {
			next_opcode();
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
		} else if (!debugger->step_by_step) {
			next_opcode();
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
