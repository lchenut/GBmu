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

#include <stringft.h>

static inline size_t	ft_strnlen__(const char *s, size_t maxlen)
{
	const char			*tmp;

	tmp = s;
	while (*tmp && maxlen)
	{
		tmp += 1;
		maxlen -= 1;
	}
	return (tmp - s);
}

char					*ft_strndup(const char *s, size_t n)
{
	char				*ret;
	char				*tmp;
	size_t				len;

	len = ft_strnlen__(s, n);
	if (!(ret = malloc(len + 1)))
		return (NULL);
	ret[len] = 0;
	tmp = ret;
	while (len--)
	{
		*tmp = *s;
		s += 1;
		tmp += 1;
	}
	return (ret);
}
