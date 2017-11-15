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

t_lst		*lst_new(void)
{
	t_lst	*ret;

	ret = (t_lst *)malloc(sizeof(t_lst));
	if (!ret)
	{
		exit(-1);
	}
	ret->head = NULL;
	ret->tail = NULL;
	ret->size = 0;
	return (ret);
}
