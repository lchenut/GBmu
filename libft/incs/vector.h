/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_norris_loves_the_norminette.h                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuck <chuck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2042/02/30 42:00:00 by chuck             #+#    #+#             */
/*   Updated: 2042/02/30 41:59:59 by chuck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "basics.h"
# define VECTOR_DFL_SIZE 128

typedef struct		s_vector
{
	void			**data;
	size_t			limit;
	size_t			current;
}					t_vector;

t_vector			*vector_new(void);
void				vector_del(t_vector *this, void (*fn)(void *));

void				vector_clear(t_vector *this, void (*fn)(void *));

size_t				vector_len(t_vector *this);

void				vector_push_front(t_vector *this, void *data);
void				vector_push_back(t_vector *this, void *data);
void				vector_insert(t_vector *this, void *data, size_t pos);
void				vector_insert_when_match(t_vector *this, void *data,
		bool(*fn)(void *, void *));

void				*vector_pop_front(t_vector *this);
void				*vector_pop_back(t_vector *this);
void				*vector_pop_index(t_vector *this, size_t pos);

void				*vector_get(t_vector *this, size_t pos);
void				*vector_get_first(t_vector *this);
void				*vector_get_last(t_vector *this);
int					vector_get_index(t_vector *this, void *data);

void				vector_iter0(t_vector *this, void (*fn)(void *));
void				vector_iter(t_vector *this, void (*fn)(void *, void *),
		void *ctx);
void				vector_iter2(t_vector *this,
		void (*fn)(void *, void *, void *),
		void *ctx1, void *ctx2);
void				vector_iteri0(t_vector *this, void (*fn)(void *, int));
void				vector_iteri(t_vector *this,
		void (*fn)(void *, void *, int), void *ctx);
void				vector_iteri2(t_vector *this,
		void (*fn)(void *, void *, void *, int),
		void *ctx1, void *ctx2);

void				vector_iterp(t_vector *this,
		void (*fn)(void *, void *, void*),
		void *ctx);
void				vector_itern(t_vector *this,
		void (*fn)(void *, void *, void*),
		void *ctx);

t_vector			*vector_copy(t_vector *this);
t_vector			*vector_map0(t_vector *this, void *(*fn)(void *));
t_vector			*vector_map(t_vector *this, void *(*fn)(void *, void *),
		void *ctx);
t_vector			*vector_map2(t_vector *this,
		void *(*fn)(void *, void *, void *),
		void *ctx1, void *ctx2);
t_vector			*vector_mapi0(t_vector *this, void *(*fn)(void *, int));
t_vector			*vector_mapi(t_vector *this,
		void *(*fn)(void *, void *, int),
		void *ctx);
t_vector			*vector_mapi2(t_vector *this,
		void *(*fn)(void *, void *, void *, int),
		void *ctx1, void *ctx2);

bool				vector_exists0(t_vector *this, bool (*fn)(void *));
bool				vector_exists(t_vector *this, bool (*fn)(void *, void *),
		void *ctx);

void				*vector_find0(t_vector *this, bool (*fn)(void *));
void				*vector_find(t_vector *this, bool (*fn)(void *, void *),
		void *ctx);
void				*vector_find0_pop(t_vector *this, bool (*fn)(void *));
void				*vector_find_pop(t_vector *this, bool (*fn)(void *, void *),
		void *ctx);
void				*vector_find0_rev(t_vector *this, bool (*fn)(void *));
void				*vector_find_rev(t_vector *this, bool (*fn)(void *, void *),
		void *ctx);
void				*vector_find0_rev_pop(t_vector *this, bool (*fn)(void *));
void				*vector_find_rev_pop(t_vector *this,
		bool (*fn)(void *, void *), void *ctx);

t_vector			*vector_find0_all(t_vector *this, bool (*fn)(void *));
t_vector			*vector_find_all(t_vector *this, bool (*fn)(void *, void *),
		void *ctx);
t_vector			*vector_find0_all_pop(t_vector *this, bool (*fn)(void *));
t_vector			*vector_find_all_pop(t_vector *this,
		bool (*fn)(void *, void *), void *ctx);

void				vector_sortq(t_vector *this,
		int (*fn)(const void *, const void *));
void				vector_sortinsert(t_vector *this,
		int (*fn)(const void *, const void *));
void				vector_sortbubble(t_vector *this,
		int (*fn)(const void *, const void *));
void				vector_sortbogo(t_vector *this,
		int (*fn)(const void *, const void *));

void				vector_rev(t_vector *this);
void				vector_shuffle(t_vector *this);

void				vector_cat(t_vector *this, t_vector *next);
void				vector_extends_front(t_vector *this, t_vector *prev);
void				vector_extends_back(t_vector *this, t_vector *next);

int					vector_realloc__(t_vector *this);

#endif
