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

char			*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t		i;
	int			j;

	i = n;
	j = 0;
	while (i > 0 && src[j] != '\0')
	{
		dst[j] = src[j];
		i--;
		j++;
	}
	while (i > 0)
	{
		dst[j] = '\0';
		i--;
		j++;
	}
	return (dst);
}
