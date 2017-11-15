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

static inline char	*ft_lltoa_neg(long long val, char *ret)
{
	int		ind;
	char	*nbr;
	char	*tmp;

	ind = 21;
	while (val)
	{
		ret[ind--] = (-(val % 10)) + 0x30;
		val /= 10;
	}
	ret[ind] = '-';
	nbr = (char *)malloc(sizeof(char) * (24 - ind));
	tmp = nbr;
	while (ret[ind])
	{
		*tmp = ret[ind];
		tmp++;
		ind++;
	}
	*tmp = 0;
	return (nbr);
}

static inline char	*ft_lltoa_pos(long long val, char *ret)
{
	int		ind;
	char	*nbr;
	char	*tmp;

	ind = 21;
	while (val)
	{
		ret[ind--] = (val % 10) + 0x30;
		val /= 10;
	}
	ind++;
	nbr = (char *)malloc(sizeof(char) * (24 - ind));
	tmp = nbr;
	while (ret[ind])
	{
		*tmp = ret[ind];
		tmp++;
		ind++;
	}
	*tmp = 0;
	return (nbr);
}

char				*ft_lltoa(long long val)
{
	char			ret[24];
	void			*ret_;

	ret_ = ret;
	((long long int *)ret_)[0] = 0;
	((long long int *)ret_)[1] = 0;
	((long long int *)ret_)[2] = 0;
	if (val < 0)
	{
		ret[22] = (-(val % 10)) + 0x30;
		return (ft_lltoa_neg(val / 10, ret));
	}
	ret[22] = (val % 10) + 0x30;
	return (ft_lltoa_pos(val / 10, ret));
}
