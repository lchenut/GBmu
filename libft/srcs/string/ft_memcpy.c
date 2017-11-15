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

#include <stringft.h>

static inline void	memcpy_loop_forward(char *dst, const char *src, size_t n)
{
	src += n - 1;
	dst += n - 1;
	while (n)
	{
		*dst = *src;
		dst--;
		src--;
		n--;
	}
}

static inline void	memcpy_loop_backward(char *dst, const char *src, size_t n)
{
	while (n)
	{
		*dst = *src;
		dst++;
		src++;
		n--;
	}
}

void				*ft_memcpy(void *dst_, const void *src_, size_t n)
{
	const char		*src = src_;
	char			*dst;

	if (n == 0 || dst_ == src_)
		return (dst_);
	dst = (char *)dst_;
	if (src > dst)
		memcpy_loop_backward(dst, src, n);
	else
		memcpy_loop_forward(dst, src, n);
	return (dst_);
}
