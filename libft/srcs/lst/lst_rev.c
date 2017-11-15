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

void			lst_rev(t_lst *this)
{
	t_lst__		*iter;
	t_lst__		*next;
	t_lst__		*tmp;

	iter = this->head;
	while (iter)
	{
		next = iter->next;
		iter->next = iter->prev;
		iter->prev = next;
		iter = next;
	}
	tmp = this->head;
	this->head = this->tail;
	this->tail = tmp;
}
