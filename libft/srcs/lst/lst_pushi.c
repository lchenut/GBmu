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

void			lst_insert(t_lst *this, void *data, int index)
{
	t_lst__		*ltmp;
	t_lst__		*to_push;

	if (index <= 0)
		lst_push_front(this, data);
	else if (index >= this->size)
		lst_push_back(this, data);
	else
	{
		ltmp = lst_get_lst__(this, index);
		if (!ltmp)
			return ;
		to_push = lst_create_lst__(data);
		this->size += 1;
		to_push->prev = ltmp->prev;
		if (ltmp->prev)
			ltmp->prev->next = to_push;
		to_push->next = ltmp;
		ltmp->prev = to_push;
	}
}
