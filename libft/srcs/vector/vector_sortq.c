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

static inline size_t	vec_partition(void **data, size_t low, size_t high,
		int (*fn)(const void *, const void *))
{
	size_t		fh;
	void		*swap;

	fh = low;
	while (low < high)
	{
		if (fn(data[low], data[high]) <= 0)
		{
			swap = data[fh];
			data[fh] = data[low];
			data[low] = swap;
			fh += 1;
		}
		low += 1;
	}
	swap = data[fh];
	data[fh] = data[low];
	data[low] = swap;
	return (fh);
}

static void				vec_sortq(void **data, size_t low, size_t high,
		int (*fn)(const void *, const void *))
{
	size_t		part;

	if (high > low)
	{
		part = vec_partition(data, low, high, fn);
		if (part != 0)
			vec_sortq(data, low, part - 1, fn);
		vec_sortq(data, part + 1, high, fn);
	}
}

void					vector_sortq(t_vector *this,
		int (*fn)(const void *, const void *))
{
	if (this->current < 2)
		return ;
	vec_sortq(this->data, 0, this->current - 1, fn);
}
