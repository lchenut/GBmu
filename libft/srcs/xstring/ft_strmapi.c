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

char			*ft_strmapi(char const *str, char (*fn)(char, int))
{
	int			index;
	char		*ret;
	char		*tmp_;

	if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	index = 0;
	tmp_ = ret;
	while (*str)
	{
		*tmp_ = fn(*str, index);
		tmp_ += 1;
		ret += 1;
		index += 1;
	}
	return (ret);
}
