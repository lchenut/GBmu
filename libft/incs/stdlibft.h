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

#ifndef STDLIBFT_H
# define STDLIBFT_H

# include "basics.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

extern long int	g_random_next;

int				ft_atoi(const char *str);
long long int	ft_atoll(const char *str);

long int		ft_random(void);
void			ft_srandom(long int seed);
void			ft_srandom_self(void);

void			*ft_calloc(size_t size);

#endif
