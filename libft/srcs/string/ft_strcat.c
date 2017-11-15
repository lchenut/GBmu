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

char			*ft_strcat(char *s1, const char *s2)
{
	char		*tmp;

	tmp = s1;
	while (*tmp)
	{
		tmp += 1;
	}
	while (*s2)
	{
		*tmp = *s2;
		tmp += 1;
		s2 += 1;
	}
	*tmp = 0;
	return (s1);
}
