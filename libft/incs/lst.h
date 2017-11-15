/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchenut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2042/02/30 41:59:59 by chuck             #+#    #+#             */
/*   Updated: 2042/02/30 41:59:59 by chuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_H
# define LST_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct		s_lst__
{
	struct s_lst__	*prev;
	struct s_lst__	*next;
	void			*data;
}					t_lst__;

typedef struct		s_lst
{
	t_lst__			*head;
	t_lst__			*tail;
	int				size;
}					t_lst;

t_lst				*lst_new(void);
void				lst_del(t_lst *this, void (*f)(void *));

t_lst				*lst_copy(t_lst *this, void *(*f)(void *));
void				lst_clear(t_lst *this, void (*f)(void *));

t_lst__				*lst_get_lst__(t_lst *this, int index);
t_lst__				*lst_create_lst__(void *data);

void				lst_push_front(t_lst *this, void *data);
void				lst_push_back(t_lst *this, void *data);
void				lst_insert(t_lst *this, void *data, int index);
void				*lst_pop_front(t_lst *this);
void				*lst_pop_back(t_lst *this);
void				*lst_pop(t_lst *this, int index);
void				*lst_get(t_lst *this, int index);
void				*lst_first(t_lst *this);
void				*lst_last(t_lst *this);

void				lst_iter(t_lst *this, void (*f)(void *, void *),
		void *context);
void				lst_iter2(t_lst *this, void (*f)(void *, void *, void *),
		void *ctx1, void *ctx2);
void				lst_iter0(t_lst *this, void (*f)(void *));
void				*lst_find(t_lst *this, bool (*f)(void *, void *),
		void *context);
void				*lst_find_pop(t_lst *this, bool (*f)(void *, void *),
		void *context);
void				*lst_find0(t_lst *this, bool (*f)(void *));
bool				lst_exists(t_lst *this, bool (*f)(void *, void *),
		void *context);

void				lst_rev(t_lst *this);

void				lst_clear_if(t_lst *this, void (*del_fn)(void *),
		bool (*find_fn)(void *, void *), void *context);

int					lst_len(t_lst *this);

#endif
