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

void			lst_clear(t_lst *this, void (*del_fn)(void *))
{
	t_lst__		*head;
	t_lst__		*ltmp;

	head = this->head;
	if (del_fn != NULL)
	{
		while (head)
		{
			ltmp = head->next;
			del_fn(head->data);
			free(head);
			head = ltmp;
		}
	}
	else
	{
		while (head)
		{
			ltmp = head->next;
			free(head);
			head = ltmp;
		}
	}
	this->size = 0;
}
