#include "scroll.h"

t_scroll          *scroll_new(size_t total, size_t size, size_t posx,
		size_t posy, size_t width, size_t height)
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
