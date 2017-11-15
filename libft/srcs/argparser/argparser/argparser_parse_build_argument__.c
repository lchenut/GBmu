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

static void			set_err_msg(char *msg, char *key,
		t_argparser_result *result)
{
	char			*err_msg;
	size_t			index;

	err_msg = ft_strnew(ft_strlen(msg) + ft_strlen(key) + 2);
	index = 0;
	result->err_msg = err_msg;
	while (msg[index])
	{
		*err_msg = msg[index];
		err_msg += 1;
		index += 1;
	}
	err_msg[0] = ':';
	err_msg[1] = ' ';
	err_msg += 2;
	index = 0;
	while (key[index])
	{
		*err_msg = key[index];
		err_msg += 1;
		index += 1;
	}
}

static void			handle_has_option_argument(char *key,
		t_argparser_result_item *result_item,
		t_argparser_result *result, t_lst *tokens)
{
	char			*first;

	if (result_item->argparser_argument->flags & ARGP_HAS_OPTION_ARGUMENT)
	{
		first = lst_first(tokens);
		if (first && first[0] != '-')
		{
			result_item->option_argument = ft_strdup(lst_pop_front(tokens));
		}
		else
		{
			set_err_msg(ERR_MSG_ARGUMENT_REQUIRED, key, result);
		}
	}
}

void				argparser_parse_build_argument__(char *key,
		t_argparser_result *result, t_lst *tokens)
{
	t_argparser_argument	*argument;
	t_argparser_result_item	*result_item;

	argument = argparser_argument_mgr_find_by_key(
			result->argparser->arguments, key);
	if (argument)
	{
		result_item = argparser_result_item_new(argument);
		lst_push_back(result->result_items, result_item);
		handle_has_option_argument(key, result_item, result, tokens);
	}
	else
	{
		set_err_msg(ERR_MSG_ILLEGAL_OPTION, key, result);
	}
}
