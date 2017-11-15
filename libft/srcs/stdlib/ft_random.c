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

long int	g_random_next = 1;

long int		ft_random(void)
{
	if (g_random_next == 0)
		g_random_next = 123459876;
	g_random_next = ((g_random_next * 1103515245) + 12345) & 0x7fffffffffffffff;
	return (g_random_next);
}
