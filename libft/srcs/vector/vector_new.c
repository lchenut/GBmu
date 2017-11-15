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

t_vector			*vector_new(void)
{
	t_vector		*this;
	size_t			index;

	if (!(this = (t_vector *)malloc(sizeof(t_vector))))
	{
		return (NULL);
	}
	if (!(this->data = (void **)malloc(sizeof(void *) * VECTOR_DFL_SIZE)))
	{
		free(this);
		return (NULL);
	}
	index = 0;
	while (index < VECTOR_DFL_SIZE)
	{
		this->data[index] = NULL;
		index += 1;
	}
	this->limit = VECTOR_DFL_SIZE;
	this->current = 0;
	return (this);
}
