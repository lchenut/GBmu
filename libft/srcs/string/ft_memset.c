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

void			*ft_memset(void *b, int c, size_t len)
{
	unsigned long	ul;
	unsigned long	*pul;
	char			*s;

	ul = (char)c;
	ul = ul | (ul << 8);
	ul = ul | (ul << 16);
	ul = ul | (ul << 32);
	pul = (unsigned long *)b;
	while (len > 8)
	{
		*pul = ul;
		pul++;
		len -= 8;
	}
	s = (char *)pul;
	while (len)
	{
		*s = (char)c;
		s++;
		len--;
	}
	return (b);
}
