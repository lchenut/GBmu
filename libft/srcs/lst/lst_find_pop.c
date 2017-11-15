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

void			*lst_find_pop(t_lst *this,
		bool (*f)(void *, void *), void *context)
{
	t_lst__		*ltmp;
	void		*data;

	ltmp = this->head;
	while (ltmp)
	{
		if (f(ltmp->data, context))
			break ;
		ltmp = ltmp->next;
	}
	if (!ltmp)
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
