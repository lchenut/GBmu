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

void			lst_iter2(t_lst *this, void (*f)(void *, void *, void *),
		void *ctx1, void *ctx2)
{
	t_lst__		*ltmp;

	ltmp = this->head;
	while (ltmp)
	{
		f(ltmp->data, ctx1, ctx2);
		ltmp = ltmp->next;
	}
}
