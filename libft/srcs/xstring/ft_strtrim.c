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

char			*ft_strtrim(const char *s)
{
	int			beg;
	int			end;
	char		*str;

	beg = 0;
	end = (int)ft_strlen(s) - 1;
	while (ft_isspace(s[beg]))
		beg++;
	if (beg > end)
		return (ft_strnew(0));
	while (end > 0 && ft_isspace(s[end]))
		end--;
	str = ft_strnew(end - beg + 2);
	str = ft_strncpy(str, s + beg, end - beg + 1);
	return (str);
}
