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

#include "get_next_line.h"

static t_gnl	*gnl_init_struct(int fd)
{
	int		size;
	t_gnl	*gnl;

	if (!(gnl = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	if (!(gnl->str = (char *)malloc(sizeof(char) * BUFF_SIZE)))
	{
		free(gnl);
		return (NULL);
	}
	if ((size = read(fd, gnl->str, BUFF_SIZE)) < 0)
	{
		free(gnl->str);
		free(gnl);
		return (NULL);
	}
	gnl->index = 0;
	gnl->size = size;
	gnl->fd = fd;
	gnl->next = NULL;
	return (gnl);
}

int				gnl_cnt_end_line(t_gnl *gnl, int fd)
{
	int		index;
	int		size;
	t_gnl	*tmp;

	size = 0;
	index = gnl->index;
	while (index < gnl->size && gnl->str[index] != '\n')
	{
		index++;
		size++;
		if (index == gnl->size && gnl->size == BUFF_SIZE)
		{
			if (!(tmp = gnl_init_struct(fd)))
				return (-1);
			tmp->next = gnl->next;
			gnl->next = tmp;
			gnl = gnl->next;
			index = 0;
		}
	}
	return (size);
}

static t_gnl	*gnl_destroy(t_gnl **begin, t_gnl **tmp)
{
	if (tmp[1])
		tmp[1]->next = tmp[0]->next;
	else
		*begin = tmp[0]->next;
	free(tmp[0]->str);
	tmp[0]->str = NULL;
	free(tmp[0]);
	tmp[0] = NULL;
	if (tmp[1])
		return (tmp[1]->next);
	return (*begin);
}

int				gnl_print(t_gnl **begin, t_gnl **tmp, int size, char **line)
{
	int i;

	if (size < 0 || !(*line = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	i = 0;
	while (size > 0)
	{
		(*line)[i++] = (tmp[0]->str[tmp[0]->index++]);
		if (tmp[0]->index == tmp[0]->size)
			tmp[0] = gnl_destroy(begin, tmp);
		size--;
	}
	(*line)[i] = '\0';
	if (!tmp[0] || (tmp[0]->index == tmp[0]->size && tmp[0]->size < BUFF_SIZE))
	{
		if (tmp[0])
			gnl_destroy(begin, tmp);
		return (0);
	}
	tmp[0]->index = tmp[0]->index + 1;
	if (tmp[0]->index == tmp[0]->size)
		tmp[0] = gnl_destroy(begin, tmp);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static t_gnl	*begin = NULL;
	t_gnl			*tmp[2];
	int				size;

	if (!line)
		return (-1);
	if (!begin)
	{
		if (!(begin = gnl_init_struct(fd)))
			return (-1);
	}
	tmp[0] = begin;
	tmp[1] = NULL;
	while (tmp[0]->fd != fd)
	{
		if (!(tmp[0]->next))
		{
			if (!(tmp[0]->next = gnl_init_struct(fd)))
				return (-1);
		}
		tmp[1] = tmp[0];
		tmp[0] = tmp[0]->next;
	}
	size = gnl_cnt_end_line(tmp[0], fd);
	return (gnl_print(&begin, tmp, size, line));
}
