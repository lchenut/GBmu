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

void			ft_bzero(void *s, size_t n)
{
	long long	*l;
	char		*c;

	l = (long long *)s;
	while (n > 8)
	{
		*l = 0;
		l++;
		n = n - 8;
	}
	c = (char *)l;
	while (n > 0)
	{
		*c = 0;
		c++;
		n--;
	}
}
