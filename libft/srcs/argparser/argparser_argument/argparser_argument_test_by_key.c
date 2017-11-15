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
#include "argparser/argparser_argument.h"

bool	argparser_argument_test_by_key(t_argparser_argument *this, char *key)
{
	if (key[0] && !key[1])
	{
		return (this->char_key == *key);
	}
	else if (key[0])
	{
		return (ft_strequ(this->str_key, key));
	}
	else
	{
		return (false);
	}
}
