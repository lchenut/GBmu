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

static void			print_usage(t_argparser *this)
{
	char			*option_chars;

	option_chars = argparser_argument_mgr_get_all_chars(this->arguments);
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(this->name, 2);
	ft_putchar_fd(' ', 2);
	if (this->usage_text)
	{
		ft_putendl_fd(this->usage_text, 2);
	}
	else if (*option_chars)
	{
		ft_putstr_fd("[-", 2);
		ft_putstr_fd(option_chars, 2);
		ft_putstr_fd("]\n", 2);
	}
}

static void			print_fn(void *data)
{
	t_argparser_argument	*argument;

	argument = data;
	ft_putchar_fd('-', 2);
	ft_putchar_fd(argument->char_key, 2);
	if (argument->str_key)
	{
		ft_putstr_fd(", --", 2);
		ft_putstr_fd(argument->str_key, 2);
	}
	if (argument->flags)
	{
		ft_putstr_fd(" arg", 2);
	}
	if (argument->help)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(argument->help, 2);
	}
	ft_putchar_fd('\n', 2);
}

void				argparser_print_help(t_argparser *this)
{
	print_usage(this);
	lst_iter0(this->arguments, print_fn);
}
