#include "scroll.h"

void              scroll_del(t_scroll *this)
{
	if (!this) {
		return ;
	}
	free(this);
}
