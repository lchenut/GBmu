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

#ifndef ARRAY_H
# define ARRAY_H

# include "basics.h"

char			**array_new(size_t size);
void			array_del(char **this);

char			**array_dup(char **this);

size_t			array_len(char **this);

void			array_dump(char **this);

void			array_iter(char **this, void (*fn)(char *));
void			array_iteri(char **this, void (*fn)(char *, int));

char			**array_map(char **this, char *(*fn)(char *));
char			**array_mapi(char **this, char *(*fn)(char *, int));

#endif
