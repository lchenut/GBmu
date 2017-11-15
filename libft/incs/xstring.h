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

#ifndef XSTRING_H
# define XSTRING_H

# include "basics.h"

/*
** Allocate and free part of memory
*/

void			*ft_memalloc(size_t size);
void			*ft_memdup(void *s, size_t len);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
char			*ft_strfnew(size_t len, char c);
void			ft_strdel(char **str);

/*
** Set characters of a string
*/

void			ft_capitalize(char *s);
void			ft_minimalize(char *s);
void			ft_strclr(char *str);

/*
** Iterate on a string
*/

void			ft_striter(char *str, void (*fn)(char *));
void			ft_striteri(char *str, void (*fn)(char *, int));
char			*ft_strmap(char const *str, char (*fn)(char));
char			*ft_strmapi(char const *str, char (*fn)(char, int));

/*
** Compare two strings
*/

int				ft_strequ(const char *s1, const char *s2);
int				ft_strnequ(const char *s1, const char *s2, size_t n);

/*
** Works on string
*/

char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strjoinfree(const char *s1, const char *s2, char c);
char			*ft_strtrim(const char *s);
char			*ft_strsub(const char *s, unsigned int start, size_t len);
char			*ft_strrep_unprint_char(const char *s);

/*
** Splits
*/

char			**ft_split(char *str);
char			**ft_strsplit(const char *str, char c);
char			**ft_strsplit_empty(const char *str, char c);

/*
** Is string...
*/

bool			ft_strisnum(const char *str);

#endif
