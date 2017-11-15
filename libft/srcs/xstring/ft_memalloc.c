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

#include <xstring.h>

void			*ft_memalloc(size_t size)
{
	void		*ret;
	char		*str;
	long long	*ll;

	if (!(ret = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	ll = (long long *)ret;
	while (size > 7)
	{
		*ll = 0;
		ll += 1;
		size -= 8;
	}
	str = (char *)ll;
	while (size)
	{
		*str = 0;
		str += 1;
		size -= 1;
	}
	return (ret);
}
