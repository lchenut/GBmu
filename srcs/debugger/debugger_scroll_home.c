#include "debugger.h"

void			debugger_scroll_home(t_debugger *this)
{
	if (this->scroll_xxd->current > 0) {
		this->scroll_xxd->current = 0;
	//	debugger_dump(this);
	}
}
