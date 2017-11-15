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

char			*ft_strstr(const char *s1, const char *s2)
{
	size_t		index;

	while (*s1)
	{
		if (*s1 == *s2)
		{
			index = 0;
			while (s1[index] && s1[index] == s2[index])
				index += 1;
			if (!s2[index])
				return ((char *)s1);
		}
		s1 += 1;
	}
	return (NULL);
}
