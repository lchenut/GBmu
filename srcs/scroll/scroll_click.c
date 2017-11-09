#include "scroll.h"

bool		scroll_click(t_scroll *this, size_t x, size_t y)
{
	if (x >= this->posx && x <= this->posx + this->width) {
		if (y >= this->posy && y <= this->posy + this->width) {
			if (this->current > 0) {
				this->current -= 1;
				return (true);
			}
		} else if (y >= this->posy + this->height - this->width &&
				y <= this->posy + this->height) {
			if (this->current + 1 < this->total - this->size) {
				this->current += 1;
				return (true);
			}
		} else if (y > this->posy + this->width &&
				y <= this->posy + this->width +
				(this->current * (this->height - this->width * 2)) / this->total) {
			if (this->current < this->size && this->current) {
				this->current = 0;
				return (true);
			} else if (this->current) {
				this->current -= this->size;
				return (true);
			}
		} else if (y > this->posy + this->width +
				(this->current + this->size) *
				(this->height - this->width * 2) / this->total &&
				y < this->posy + this->height - this->width) {
			if (this->current + 2 * this->size < this->total) {
				this->current += this->size;
				return (true);
			} else if (this->current + 2 * this->size >= this->total) {
				this->current = this->total - this->size - 1;
				return (true);
			}
		}
	}
	return (false);
}
