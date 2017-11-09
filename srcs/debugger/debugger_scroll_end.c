#include "debugger.h"

void			debugger_scroll_end(t_debugger *this)
{
	if (this->scroll_xxd->current < this->scroll_xxd->total - this->scroll_xxd->size - 1) {
		this->scroll_xxd->current = this->scroll_xxd->total - this->scroll_xxd->size - 1;
		debugger_dump(this);
	}
}
