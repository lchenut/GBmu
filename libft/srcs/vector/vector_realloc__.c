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

int				vector_realloc__(t_vector *this)
{
	void		**new;

	if (!(new = (void **)malloc(sizeof(void *) * (this->limit * 2))))
	{
		return (-1);
	}
	ft_memcpy(new, this->data, (this->limit * sizeof(void *)));
	free(this->data);
	this->limit *= 2;
	this->data = new;
	return (0);
}
