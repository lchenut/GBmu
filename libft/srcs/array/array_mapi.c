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

#include <array.h>

char			**array_mapi(char **this, char *(*fn)(char *, int))
{
	char		**ret;
	size_t		len;
	size_t		index;

	len = array_len(this);
	if (!(ret = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	index = 0;
	while (index < len)
	{
		ret[index] = fn(this[index], index);
		index += 1;
	}
	ret[index] = NULL;
	return (ret);
}
