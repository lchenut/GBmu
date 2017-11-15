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

char			*ft_strmap(char const *str, char (*fn)(char))
{
	char		*ret;
	char		*tmp_;

	if (!(ret = (char *)malloc(sizeof(char) * (strlen(str)))))
		return (NULL);
	tmp_ = ret;
	while (*str)
	{
		*tmp_ = fn(*str);
		tmp_ += 1;
	}
	return (ret);
}
