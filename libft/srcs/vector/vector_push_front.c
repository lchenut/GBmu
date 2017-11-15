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

void			vector_push_front(t_vector *this, void *data)
{
	if (this->limit == this->current + 1)
	{
		if (vector_realloc__(this))
			return ;
	}
	ft_memmove(this->data + 1, this->data, this->current * sizeof(void *));
	this->data[0] = data;
	this->current += 1;
}
