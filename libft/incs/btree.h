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

#ifndef BTREE_H
# define BTREE_H

# include "basics.h"

typedef struct			s_btree_node
{
	void				*data;
	struct s_btree_node	*parent;
	struct s_btree_node *left;
	struct s_btree_node *right;
	size_t				size_l;
	size_t				size_r;
}						t_btree_node;

t_btree_node			*btree_node_new(void *data);
void					btree_node_del(t_btree_node *this,
		void (*del_fn)(void *));

typedef struct			s_btree
{
	int					(*cmp_fn)(void *, void *);
	t_btree_node		*root;
}						t_btree;

t_btree					*btree_new(int (*cmp_fn)(void *, void *));
void					btree_del(t_btree *this, void (*del)(void *));

void					btree_insert(t_btree *this, void *data);
void					btree_iter(t_btree *this, void (*iter_fn)(void *));

bool					btree_exists(t_btree *this, void *data);

#endif
