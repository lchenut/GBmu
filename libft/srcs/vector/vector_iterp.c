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

void			vector_iterp(t_vector *this, void (*fn)(void *, void *, void *),
																void *ctx)
{
	size_t		index;
	void		*prev;

	index = 0;
	prev = NULL;
	while (index < this->current)
	{
		fn(this->data[index], prev, ctx);
		prev = this->data[index];
		index += 1;
	}
}
