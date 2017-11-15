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

#include "lst.h"

bool			lst_exists(t_lst *this,
		bool (*f)(void *, void *), void *context)
{
	t_lst__		*ltmp;

	ltmp = this->head;
	while (ltmp)
	{
		if (f(ltmp->data, context))
			return (1);
		ltmp = ltmp->next;
	}
	return (0);
}
