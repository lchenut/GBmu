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

static inline t_lst__	*foundlst(t_lst *this,
		t_lst__ *ltmp, void (*del_fn)(void *))
{
	t_lst__		*ltmp_;

	if (del_fn)
		del_fn(ltmp->data);
	if (ltmp->prev)
		ltmp->prev->next = ltmp->next;
	else
		this->head = ltmp->next;
	if (ltmp->next)
		ltmp->next->prev = ltmp->prev;
	else
		this->tail = ltmp->prev;
	this->size -= 1;
	ltmp_ = ltmp->next;
	free(ltmp);
	return (ltmp_);
}

void					lst_clear_if(t_lst *this, void (*del_fn)(void *),
		bool (*find_fn)(void *, void *), void *context)
{
	t_lst__		*ltmp;

	ltmp = this->head;
	while (ltmp)
	{
		if (find_fn(ltmp->data, context))
		{
			ltmp = foundlst(this, ltmp, del_fn);
		}
		else
		{
			ltmp = ltmp->next;
		}
	}
}
