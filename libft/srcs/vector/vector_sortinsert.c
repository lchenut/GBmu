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

void			vector_sortinsert(t_vector *this,
										int (*fn)(const void *, const void *))
{
	void		**data;
	void		*swap;
	size_t		index;
	size_t		rewind;

	data = this->data;
	index = 1;
	while (index < this->current)
	{
		rewind = index - 1;
		while (rewind < this->current && fn(data[rewind], data[rewind + 1]) > 0)
		{
			swap = data[rewind];
			data[rewind] = data[rewind + 1];
			data[rewind + 1] = swap;
			rewind -= 1;
		}
		index += 1;
	}
}
