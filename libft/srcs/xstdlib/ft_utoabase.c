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

#include "xstdlib.h"

#define BUFFER_MAX ((sizeof(long long) * 8) + 1)

const char	*g_set_base = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char		*ft_utoabase(register unsigned long long val, register int base)
{
	char	buf[65];
	char	*p;
	char	*ret;
	char	*tmp;

	p = &(buf[64]);
	*(p--) = 0;
	if (base < 2 || base > 36)
		base = 10;
	*(p--) = g_set_base[val % base];
	val /= base;
	while (val)
	{
		*(p--) = g_set_base[val % base];
		val /= base;
	}
	if (!(ret = (char *)malloc(sizeof(char) * (buf + 65 - p))))
		return (NULL);
	tmp = ret;
	while (*++p)
		*tmp++ = *p;
	*tmp = 0;
	return (ret);
}
