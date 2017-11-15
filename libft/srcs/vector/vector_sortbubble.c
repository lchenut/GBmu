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

void			vector_sortbubble(t_vector *this,
										int (*fn)(const void *, const void *))
{
	void		*swap;
	size_t		index;
	size_t		max;

	max = this->current;
	while (max > 1)
	{
		index = 1;
		while (index < max)
		{
			if (fn(this->data[index - 1], this->data[index]) > 0)
			{
				swap = this->data[index - 1];
				this->data[index - 1] = this->data[index];
				this->data[index] = swap;
			}
			index += 1;
		}
		max -= 1;
	}
}
