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

t_lst			*lst_copy(t_lst *this, void *(*f)(void *))
{
	t_lst		*copy;
	t_lst__		*ltmp;

	copy = lst_new();
	ltmp = this->head;
	if (f)
	{
		while (ltmp)
		{
			lst_push_back(copy, f(ltmp->data));
			ltmp = ltmp->next;
		}
	}
	else
	{
		while (ltmp)
		{
			lst_push_back(copy, ltmp->data);
			ltmp = ltmp->next;
		}
	}
	return (copy);
}
