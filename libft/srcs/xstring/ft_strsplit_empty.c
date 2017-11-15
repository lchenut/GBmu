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

#include "xstring.h"

static int	cpt_tab(const char *str, char sep)
{
	int		cpt;

	cpt = 1;
	while (*str)
	{
		cpt += (*str == sep);
		str += 1;
	}
	return (cpt);
}

static int	cpt_word(const char *str, char sep)
{
	const char	*start;

	start = str;
	while (*str && *str != sep)
	{
		str += 1;
	}
	return (str - start);
}

char		**ft_strsplit_empty(const char *str, char sep)
{
	int		size;
	int		word;
	int		index;
	char	**ret;

	size = cpt_tab(str, sep);
	ret = malloc(sizeof(char *) * (size + 1));
	ret[size] = NULL;
	index = 0;
	while (*str)
	{
		word = cpt_word(str, sep);
		ret[index] = ft_strndup(str, word);
		str += word + (str[word] != 0);
		index += 1;
	}
	return (ret);
}
