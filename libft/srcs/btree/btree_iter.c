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

static void		btree_node_iter(t_btree_node *this, void (*iter_fn)(void *))
{
	if (this->left)
	{
		btree_node_iter(this->left, iter_fn);
	}
	iter_fn(this->data);
	if (this->right)
	{
		btree_node_iter(this->right, iter_fn);
	}
}

void			btree_iter(t_btree *this, void (*iter_fn)(void *))
{
	btree_node_iter(this->root, iter_fn);
}
