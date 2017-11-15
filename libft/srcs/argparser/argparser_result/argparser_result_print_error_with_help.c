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

void		argparser_result_print_error_with_help(t_argparser_result *this)
{
	if (this->err_msg)
	{
		ft_putstr_fd(this->argparser->name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(this->err_msg, 2);
	}
	argparser_print_help(this->argparser);
}
