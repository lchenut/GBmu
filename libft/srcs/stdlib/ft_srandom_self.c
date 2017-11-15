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

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

long int		g_random_next;

void			ft_srandom_self(void)
{
	int			fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
	{
		g_random_next = (long int)(&fd) ^ (long int)(ft_srandom_self);
		if (g_random_next < 0)
			g_random_next += 0x7fffffffffffffff;
		return ;
	}
	if (read(fd, &g_random_next, sizeof(g_random_next)) == -1)
	{
		close(fd);
		g_random_next = (long int)(&fd) ^ (long int)(ft_srandom_self);
		if (g_random_next < 0)
			g_random_next += 0x7fffffffffffffff;
		return ;
	}
	if (g_random_next < 0)
		g_random_next += 0x7fffffffffffffff;
	close(fd);
}
