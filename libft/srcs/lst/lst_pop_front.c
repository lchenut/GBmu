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

#include <lst.h>

void			*lst_pop_front(t_lst *this)
{
	t_lst__		*head;
	void		*data;

	if (!(head = lst_get_lst__(this, 0)))
		return (NULL);
	data = head->data;
	this->head = head->next;
	if (head->next)
	{
		this->head->prev = NULL;
	}
	else
	{
		this->tail = NULL;
	}
	this->size -= 1;
	free(head);
	return (data);
}
