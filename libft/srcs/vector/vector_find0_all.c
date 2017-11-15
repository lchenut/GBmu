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

t_vector		*vector_find0_all(t_vector *this, bool (*fn)(void *))
{
	t_vector	*ret;
	size_t		index;

	ret = vector_new();
	index = 0;
	while (index < this->current)
	{
		if (fn(this->data[index]))
			vector_push_back(ret, this->data[index]);
		index += 1;
	}
	return (ret);
}
