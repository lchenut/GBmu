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

static void		iter_fn(t_btree_node *node, void (*del_fn)(void *))
{
	if (!node)
	{
		return ;
	}
	iter_fn(node->left, del_fn);
	iter_fn(node->right, del_fn);
	del_fn(node);
}

void			btree_del(t_btree *this, void (*del_fn)(void *))
{
	iter_fn(this->root, del_fn);
	free(this);
}
