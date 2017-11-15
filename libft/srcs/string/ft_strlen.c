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

#include "stringft.h"

/*
** #define RET(a)		{if (!p[a]) return (p - str + a);}
** #define MAKE_ALL	RET(0) RET(1) RET(2) RET(3) RET(4) RET(5) RET(6) RET(7)
** static inline size_t	ft_strlen_loop(const unsigned long *lp,
** 		const char *p, const char *str)
** {
** 	static const unsigned long g_mask01 = 0x0101010101010101;
** 	static const unsigned long g_mask80 = 0x8080808080808080;
** 	while (1)
** 	{
** 		if ((*lp - g_mask01) & g_mask80)
** 		{
** 			p = (const char *)(lp);
** 			MAKE_ALL;
** 		}
** 		lp++;
** 	}
** 	return (0);
** }
** size_t					ft_strlen(const char *str)
** {
** 	const char			*p;
** 	const unsigned long	*lp;
** 	p = str;
** 	while ((long)(unsigned long *)p & (sizeof(long) - 1))
** 	{
** 		if (*p == '\0')
** 			return (p - str);
** 		p++;
** 	}
** 	lp = (const unsigned long *)p;
** 	return (ft_strlen_loop(lp, p, str));
** }
*/

size_t				ft_strlen(const char *s)
{
	const char		*p;

	p = s;
	while (*p)
	{
		p += 1;
	}
	return (p - s);
}
