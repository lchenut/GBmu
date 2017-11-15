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

char			*ft_strjoin(const char *s1, const char *s2)
{
	char		*ret;
	size_t		l1;
	size_t		l2;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(char) * (l1 + l2 + 1))))
		return (NULL);
	ft_memcpy(ret, s1, l1);
	ft_memcpy(ret + l1, s2, l2 + 1);
	return (ret);
}
