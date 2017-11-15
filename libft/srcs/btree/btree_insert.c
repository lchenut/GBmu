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

/*
** 1. Each node is either red or black.
** 2. The root is black. This rule is sometimes omitted.
** Since the root can always be changed from red to black, but not necessarily
** vice versa, this rule has little effect on analysis.
** 3. All leaves (NIL) are black.
** 4. If a node is red, then both its children are black.
** 5. Every path from a given node to any of its descendant NIL nodes contains
** the same number of black nodes. Some definitions: the number of black nodes
** from the root to a node is the node's black depth; the uniform number of
** black nodes in all paths from root to the leaves is called the black-height
** of the red–black tree.
*/

void			btree_insert(t_btree *this, void *data)
{
	t_btree_node	*new;
	t_btree_node	*last;
	int				cmp;

	new = btree_node_new(data);
	if (this->root == NULL)
	{
		this->root = new;
		return ;
	}
	last = this->root;
	while (last)
	{
		cmp = this->cmp_fn(last->data, data);
		if ((cmp > 0 && last->left) || (cmp < 0 && last->right))
			last = cmp > 0 ? last->left : last->right;
		else
		{
			if (cmp > 0)
				last->left = new;
			else
				last->right = new;
			break ;
		}
	}
}
