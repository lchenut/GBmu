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

void			*vector_pop_index(t_vector *this, size_t pos)
{
	void		*data;

	if (this->current == 0 || pos > this->current)
	{
		return (NULL);
	}
	data = this->data[pos];
	this->current -= 1;
	ft_memmove(this->data + pos, this->data + pos + 1,
										(this->current - pos) * sizeof(void *));
	this->data[this->current] = NULL;
	return (data);
}
