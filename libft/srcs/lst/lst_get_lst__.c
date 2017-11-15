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

static inline t_lst__	*lgl_tail__(t_lst *this, int index)
{
	t_lst__		*ltmp;
	int			indtmp;

	ltmp = this->tail;
	indtmp = this->size - 1;
	while (indtmp != index)
	{
		ltmp = ltmp->prev;
		indtmp -= 1;
	}
	return (ltmp);
}

static inline t_lst__	*lgl_head__(t_lst *this, int index)
{
	t_lst__		*ltmp;
	int			indtmp;

	ltmp = this->head;
	indtmp = 0;
	while (indtmp != index)
	{
		ltmp = ltmp->next;
		indtmp += 1;
	}
	return (ltmp);
}

t_lst__					*lst_get_lst__(t_lst *this, int index)
{
	t_lst__		*ltmp;

	if (index < 0 || index > this->size - 1)
		return (NULL);
	if (index < this->size / 2)
	{
		ltmp = lgl_head__(this, index);
	}
	else
	{
		ltmp = lgl_tail__(this, index);
	}
	return (ltmp);
}
