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

void			*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	register unsigned char			*st;
	register const unsigned char	*rc = src;

	st = dst;
	if (n)
	{
		if ((*st++ = *rc++) == (unsigned char)c)
			return (st);
		while (--n != 0)
		{
			if ((*st++ = *rc++) == (unsigned char)c)
				return (st);
		}
	}
	return (0);
}
