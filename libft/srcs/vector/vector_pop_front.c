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

void			*vector_pop_front(t_vector *this)
{
	void		*data;

	if (this->current == 0)
	{
		return (NULL);
	}
	data = this->data[0];
	this->current -= 1;
	ft_memmove(this->data, this->data + 1, this->current * sizeof(void *));
	return (data);
}
