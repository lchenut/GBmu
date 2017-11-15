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

#include "btree.h"

bool		btree_exists(t_btree *this, void *data)
{
	t_btree_node	*last;
	int				cmp;

	if (!this->root)
		return (false);
	last = this->root;
	while (last)
	{
		cmp = this->cmp_fn(last->data, data);
		if (cmp == 0)
		{
			return (true);
		}
		if (cmp > 0)
		{
			last = last->left;
		}
		else
		{
			last = last->right;
		}
	}
	return (false);
}
