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

char			*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		len_s1;
	size_t		len_s2;
	size_t		i;
	int			j;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	if (*s2 == '\0')
		return ((char *)s1);
	while (i + len_s2 <= len_s1 && i < n)
	{
		if (s1[i] == s2[0])
		{
			j = 0;
			while (s1[i + j] == s2[j] && s2[j] && i + j < n)
				j++;
			if (!s2[j])
				return ((char *)(s1 + i));
		}
		i++;
	}
	return (NULL);
}
