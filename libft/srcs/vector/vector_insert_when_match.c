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

void			vector_insert_when_match(t_vector *this, void *data,
		bool (*match_fn)(void *, void *))
{
	size_t		pos;

	pos = 0;
	while (pos < this->current)
	{
		if (match_fn(this->data[pos], data))
			break ;
		pos += 1;
	}
	if (this->current + 1 == this->limit)
	{
		if (vector_realloc__(this))
			return ;
	}
	if (pos == this->current)
	{
		this->data[this->current] = data;
	}
	else
	{
		ft_memmove(this->data + pos + 1, this->data + pos,
				(this->current - pos) * sizeof(void *));
		this->data[pos] = data;
	}
	this->current += 1;
}
