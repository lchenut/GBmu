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

void			*lst_pop(t_lst *this, int index)
{
	t_lst__		*ltmp;
	void		*data;

	if (index < 0)
		index += this->size;
	if (!(ltmp = lst_get_lst__(this, index)))
		return (NULL);
	data = ltmp->data;
	if (ltmp->prev)
		ltmp->prev->next = ltmp->next;
	else
		this->head = ltmp->next;
	if (ltmp->next)
		ltmp->next->prev = ltmp->prev;
	else
		this->tail = ltmp->prev;
	free(ltmp);
	this->size -= 1;
	return (data);
}
