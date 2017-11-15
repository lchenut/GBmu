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

static int	cpt_tab(const char *s, char c)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 1;
	while (s[j])
	{
		if (s[j] != c && k)
		{
			k = 0;
			i++;
		}
		else if (s[j] == c && !k)
			k = 1;
		j++;
	}
	return (i);
}

static int	cpt_word(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char		**ft_strsplit(const char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**str;

	if (!s)
		return (NULL);
	i = cpt_tab(s, c);
	if (!(str = (char **)malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	str[i] = NULL;
	j = 0;
	k = 0;
	while (k < i)
	{
		while (s[j] == c)
			j++;
		str[k] = ft_strndup((char *)(s + j), cpt_word(s + j, c));
		j = j + cpt_word(s + j, c);
		k++;
	}
	return (str);
}
