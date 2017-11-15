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

void			vector_insert(t_vector *this, void *data, size_t pos)
{
	if (pos > this->current)
	{
		vector_push_back(this, data);
		return ;
	}
	if (this->current + 1 == this->limit)
	{
		if (vector_realloc__(this))
		{
			return ;
		}
	}
	ft_memmove(this->data + pos + 1, this->data + pos,
			(this->current - pos) * sizeof(void *));
	this->data[pos] = data;
	this->current += 1;
}
