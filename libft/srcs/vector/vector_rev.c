/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_norris_loves_the_norminette.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuck <chuck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2042/02/30 42:00:00 by chuck             #+#    #+#             */
/*   Updated: 2042/02/30 41:59:59 by chuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void			vector_rev(t_vector *this)
{
	size_t		beg;
	size_t		end;
	void		*swap;

	if (this->current < 2)
		return ;
	beg = 0;
	end = this->current - 1;
	while (beg < end)
	{
		swap = this->data[beg];
		this->data[beg] = this->data[end];
		this->data[end] = swap;
		beg += 1;
		end -= 1;
	}
}
