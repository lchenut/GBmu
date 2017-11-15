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

static bool		vector_is_sort(t_vector *this,
		int (*fn)(const void *, const void *))
{
	size_t		index;

	index = 1;
	while (index < this->current)
	{
		if (fn(this->data[index - 1], this->data[index]) > 0)
			return (false);
		index += 1;
	}
	return (true);
}

void			vector_sortbogo(t_vector *this,
		int (*fn)(const void *, const void *))
{
	while (true)
	{
		if (vector_is_sort(this, fn))
			return ;
		vector_shuffle(this);
	}
}
