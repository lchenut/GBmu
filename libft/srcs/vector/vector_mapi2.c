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

t_vector		*vector_mapi2(t_vector *this,
							void *(*fn)(void *, void *, void *, int),
							void *ctx1, void *ctx2)
{
	t_vector	*ret;
	size_t		index;

	ret = vector_new();
	index = 0;
	while (index < this->current)
	{
		vector_push_back(ret, fn(this->data[index], ctx1, ctx2, (int)index));
		index += 1;
	}
	return (ret);
}
