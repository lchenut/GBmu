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

#include "xstring.h"

void			*ft_memdup(void *s, size_t len)
{
	void		*ret;
	void		*tmp;

	ret = malloc(len);
	tmp = ret;
	while (len > 8)
	{
		*((long long *)tmp) = *((long long *)s);
		tmp += 8;
		s += 8;
		len -= 8;
	}
	while (len)
	{
		*((char *)tmp) = *((char *)s);
		tmp += 1;
		s += 1;
		len -= 1;
	}
	return (ret);
}
