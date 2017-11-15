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

char			*ft_strrchr(const char *s, int c)
{
	char		*ret;

	ret = NULL;
	while (*s != 0)
	{
		if (*s == (char)c)
			ret = (char *)s;
		s++;
	}
	if (*s == (char)c)
		ret = (char *)s;
	return (ret);
}
