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

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "stdioft.h"
#include "stringft.h"

static char		g_ft_strerror_msg[1024];

static void		cat_long(size_t index, long lnum)
{
	char		buf[32];
	size_t		index_buf;

	buf[31] = 0;
	index_buf = 30;
	while (lnum)
	{
		buf[index_buf] = (lnum % 10) + '0';
		index_buf -= 1;
		lnum /= 10;
	}
	if (index_buf == 30)
		buf[index_buf] = '0';
	else
		index_buf += 1;
	ft_strcat(g_ft_strerror_msg + index, buf + index_buf);
}

static void		cat_number(int num)
{
	size_t		index;
	long		lnum;

	index = 0;
	while (g_ft_strerror_msg[index])
		index += 1;
	lnum = (long)num;
	if (lnum < 0L)
	{
		g_ft_strerror_msg[index] = '-';
		index += 1;
		g_ft_strerror_msg[index] = 0;
		lnum = -lnum;
	}
	cat_long(index, lnum);
}

char			*ft_strerror(int errnum)
{
	const char	**tab;
	int			size;

	tab = (const char **)sys_errlist;
	size = sys_nerr;
	g_ft_strerror_msg[0] = 0;
	if (errnum < 0 || errnum > size || !tab[errnum])
	{
		ft_strcat(g_ft_strerror_msg, "Unknown error ");
		cat_number(errnum);
	}
	else
	{
		ft_strcat(g_ft_strerror_msg, tab[errnum]);
	}
	return (g_ft_strerror_msg);
}
