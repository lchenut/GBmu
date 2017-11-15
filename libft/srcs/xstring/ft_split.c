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

static int	ft_cpt_wd(char *str)
{
	int test;
	int cpt;
	int i;

	test = 0;
	cpt = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			test = 0;
		else if (test == 0)
		{
			test = 1;
			cpt++;
		}
		i++;
	}
	return (cpt);
}

static int	ft_cpt_len_wd(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	return (i);
}

char		**ft_split(char *str)
{
	char	**split;
	int		nb_wd;
	int		len_wd;
	int		i;
	int		j;

	nb_wd = ft_cpt_wd(str);
	if (!(split = (char **)malloc(sizeof(char *) * (nb_wd + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
		{
			len_wd = ft_cpt_len_wd(str + i);
			split[j++] = ft_strndup(str + i, len_wd);
			i = i + len_wd;
		}
	}
	split[j] = NULL;
	return (split);
}
