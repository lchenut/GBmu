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

void			*lst_pop_back(t_lst *this)
{
	t_lst__		*tail;
	void		*data;

	tail = this->tail;
	if (!tail)
		return (NULL);
	data = tail->data;
	this->tail = tail->prev;
	if (tail->prev)
	{
		this->tail->next = NULL;
	}
	else
	{
		this->head = NULL;
	}
	this->size -= 1;
	free(tail);
	return (data);
}
