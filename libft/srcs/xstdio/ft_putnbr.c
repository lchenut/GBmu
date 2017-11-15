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

#include <xstdio.h>

static inline char	*loop_putnbr_(char *str, int index, long nbr, int f_neg)
{
	while (nbr != 0)
	{
		str[index] = nbr % 10 + '0';
		nbr /= 10;
		index -= 1;
	}
	if (f_neg == 1)
	{
		str[index] = '-';
		index -= 1;
	}
	return (str + index + 1);
}

void				ft_putnbr(int nbr_)
{
	long			nbr;
	char			str[12];
	int				index;
	int				f_neg;

	nbr = nbr_;
	str[11] = 0;
	index = 10;
	f_neg = 0;
	if (nbr < 0)
	{
		f_neg = 1;
		nbr = -nbr;
	}
	if (nbr == 0)
	{
		str[index] = '0';
		index -= 1;
	}
	ft_putstr(loop_putnbr_(str, index, nbr, f_neg));
}
