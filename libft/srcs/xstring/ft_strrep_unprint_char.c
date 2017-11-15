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

#include "xstring.h"

static size_t	new_len(const char *s)
{
	size_t		len;

	len = 0;
	while (*s)
	{
		if (*s >= 32 && *s <= 126)
			len += 2;
		else if (*s == '\n' || *s == '\t' ||
				*s == '\r' || *s == '\b' || *s == '\v')
			len += 1;
		else
			len += 4;
		s += 1;
	}
	return (len);
}

static void		place_space(char *ret, char c)
{
	*ret = '\\';
	if (c == '\n')
		ret[1] = 'n';
	else if (c == '\r')
		ret[1] = 'r';
	else if (c == '\b')
		ret[1] = 'b';
	else if (c == '\v')
		ret[1] = 'v';
	else
		ret[1] = 't';
}

static void		place_hexa(char *ret, char c)
{
	*ret = '\\';
	ret[1] = 'x';
	ret[2] = (c % 16);
	ret[2] = ret[2] < 10 ? ret[2] + '0' : ret[2] - 10 + 'a';
	ret[3] = (c / 16);
	ret[3] = ret[3] < 10 ? ret[3] + '0' : ret[3] - 10 + 'a';
}

char			*ft_strrep_unprint_char(const char *s)
{
	char		*ret;
	size_t		index;

	ret = ft_strnew(new_len(s));
	index = 0;
	while (*s)
	{
		if (*s >= 32 && *s <= 126)
			ret[index] = *s;
		else if (*s == '\n' || *s == '\t' ||
				*s == '\r' || *s == '\b' || *s == '\v')
		{
			place_space(ret + index, *s);
			index += 1;
		}
		else
		{
			place_hexa(ret + index, *s);
			index += 3;
		}
		index += 1;
		s += 1;
	}
	return (ret);
}
