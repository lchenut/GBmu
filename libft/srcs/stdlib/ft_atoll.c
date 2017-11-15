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

#include <limits.h>
#include <errno.h>
#include "stdlibft.h"

static inline long long int	ft_atoll_neg(const char *s, long long cutoff,
		int cutlim)
{
	long long	ret;
	char		c;

	ret = 0;
	while ((c = (unsigned char)*s++))
	{
		if (c > 0x2F && c < 0x3A)
			c -= 0x30;
		else
			break ;
		if (ret < cutoff || (ret == cutoff && c > cutlim))
		{
			ret = LLONG_MIN;
			errno = ERANGE;
			break ;
		}
		else
		{
			ret *= 10;
			ret -= c;
		}
	}
	return (ret);
}

static inline long long int	ft_atoll_pos(const char *s, long long cutoff,
		int cutlim)
{
	long long	ret;
	char		c;

	ret = 0;
	while ((c = (unsigned char)*s++))
	{
		if (c > 0x2F && c < 0x3A)
			c -= 0x30;
		else
			break ;
		if (ret > cutoff || (ret == cutoff && c > cutlim))
		{
			ret = LLONG_MAX;
			errno = ERANGE;
			break ;
		}
		else
		{
			ret *= 10;
			ret += c;
		}
	}
	return (ret);
}

long long int				ft_atoll(const char *s)
{
	int			c;
	int			neg;

	c = (unsigned char)*s;
	while (c == 0x20 || (c > 0x8 && c < 0xE))
		c = (unsigned char)*(++s);
	if (c == '-')
	{
		neg = 1;
		s++;
	}
	else
	{
		neg = 0;
		if (c == '+')
			s++;
	}
	if (neg)
		return (ft_atoll_neg(s, LLONG_MIN / 10, 8));
	return (ft_atoll_pos(s, LLONG_MAX / 10, 7));
}
