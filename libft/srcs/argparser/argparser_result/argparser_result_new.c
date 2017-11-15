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

#include "argparser/argparser.h"
#include "argparser/argparser_result.h"

t_argparser_result			*argparser_result_new(t_argparser *argparser,
		char *command_name)
{
	t_argparser_result		*this;

	this = ft_calloc(sizeof(t_argparser_result));
	this->argparser = argparser;
	this->command_name = ft_strdup(command_name);
	this->result_items = lst_new();
	this->remainders = lst_new();
	this->err_msg = NULL;
	return (this);
}
