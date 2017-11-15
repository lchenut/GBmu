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

int				ft_strnequ(const char *s1, const char *s2, size_t n)
{
	if (n == 0 || (*s1 == *s2 && *s1 == '\0'))
		return (1);
	if (*s1 != *s2)
		return (0);
	return (ft_strnequ(s1 + 1, s2 + 1, n - 1));
}
