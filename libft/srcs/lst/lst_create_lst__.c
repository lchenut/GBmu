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

t_lst__			*lst_create_lst__(void *data)
{
	t_lst__		*ret;

	ret = malloc(sizeof(t_lst__));
	if (!ret)
	{
		exit(-1);
	}
	ret->prev = NULL;
	ret->next = NULL;
	ret->data = data;
	return (ret);
}
