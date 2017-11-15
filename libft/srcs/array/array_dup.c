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

char			**array_dup(char **this)
{
	char		**new;
	size_t		index;

	if (!(new = (char **)malloc(sizeof(char *) * (array_len(this) + 1))))
		return (NULL);
	index = 0;
	while (this[index])
	{
		new[index] = ft_strdup(this[index]);
		index++;
	}
	new[index] = NULL;
	return (new);
}
