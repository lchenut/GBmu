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

static bool			is_valid_opt(char *str_token)
{
	if (str_token[0] == '-' && str_token[1] == '-' &&
			str_token[2] != '\0' && str_token[3] == '\0')
	{
		return (false);
	}
	return (true);
}

static void			build_argument_one_hyphen_case(char *str_token,
		t_argparser_result *result, t_lst *tokens)
{
	char			*tmp_token;
	char			char_token[2];

	char_token[0] = 0;
	char_token[1] = 0;
	tmp_token = str_token + 1;
	while (*tmp_token)
	{
		if (result->err_msg)
			break ;
		*char_token = *tmp_token;
		argparser_parse_build_argument__(char_token, result, tokens);
		tmp_token += 1;
	}
}

void				argparser_parse_build_result_item_inner__(char *str_token,
		t_argparser_result *result, t_lst *tokens)
{
	if (result->err_msg)
		return ;
	if (!is_valid_opt(str_token))
	{
		set_err_msg(ERR_MSG_ILLEGAL_OPTION, str_token, result);
		return ;
	}
	if (str_token[0] == '-' && str_token[1] == '-')
	{
		argparser_parse_build_argument__(str_token + 2, result, tokens);
	}
	else if (str_token[0] == '-')
	{
		build_argument_one_hyphen_case(str_token, result, tokens);
	}
}
