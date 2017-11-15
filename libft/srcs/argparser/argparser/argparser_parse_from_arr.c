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

#include <stdlib.h>
#include "argparser/argparser.h"
#include "argparser/argparser_result.h"

t_argparser_result	*argparser_parse_from_arr(t_argparser *this,
		char **str_tokens_arr)
{
	t_argparser_result	*result;
	t_lst				*str_tokens;

	str_tokens = lst_new();
	while (*str_tokens_arr)
	{
		lst_push_back(str_tokens, *str_tokens_arr);
		str_tokens_arr += 1;
	}
	result = argparser_parse(this, str_tokens);
	lst_del(str_tokens, NULL);
	return (result);
}
