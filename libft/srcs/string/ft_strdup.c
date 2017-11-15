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

char			*ft_strdup(const char *s1)
{
	char		*cpy;
	char		*tmp;

	if (!(cpy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	tmp = cpy;
	while (*s1)
	{
		*tmp = *s1;
		tmp += 1;
		s1 += 1;
	}
	*tmp = 0;
	return (cpy);
}
