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

int				ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n)
	{
		if (*((unsigned char *)s1++) != *((unsigned char *)s2++))
			return (*((unsigned char *)--s1) - *((unsigned char *)--s2));
		n--;
	}
	return (0);
}
