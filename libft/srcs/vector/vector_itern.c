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

void			vector_itern(t_vector *this, void (*fn)(void *, void *, void *),
																void *ctx)
{
	size_t		index;
	void		*next;

	index = 0;
	while (index < this->current)
	{
		next = (index + 1 == this->current) ? NULL : this->data[index + 1];
		fn(this->data[index], next, ctx);
		index += 1;
	}
}
