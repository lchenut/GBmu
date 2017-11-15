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

char			*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t		i;
	char		*tmp;

	i = ft_strlen(s1);
	tmp = s1;
	while (*s2 && n)
	{
		*((s1++) + i) = *(s2++);
		n--;
	}
	*((s1) + i) = 0;
	return (tmp);
}
