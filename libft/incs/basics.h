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

#ifndef BASICS_H
# define BASICS_H

/*
** # define __DEBUG
** # ifdef __DEBUG
** #  include <stdio.h>
** #  define DEBUG_FILE "/tmp/.debug_irc"
** #  define LOG_ERROR(STR, ...) {\
** 	int fd__ = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);\
** 	dprintf(fd__, "%-40.40s:%3i [\e[31;1mERROR\e[0m]: ", __FILE__, __LINE__);\
** 	dprintf(fd__, ">"STR"<\n", ##__VA_ARGS__);\
** 	close(fd__);\
** }
** #  define LOG_INFO(STR, ...) {\
** 	int fd__ = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);\
** 	dprintf(fd__, "%-40.40s:%3i [\e[32;1mINFO-\e[0m]: ", __FILE__, __LINE__);\
** 	dprintf(fd__, ">"STR"<\n", ##__VA_ARGS__);\
** 	close(fd__);\
** }
** #  define LOG_WARN(STR, ...) {\
** 	int fd__ = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);\
** 	dprintf(fd__, "%-40.40s:%3i [\e[33;1mWARN-\e[0m]: ", __FILE__, __LINE__);\
** 	dprintf(fd__, ">"STR"<\n", ##__VA_ARGS__);\
** 	close(fd__);\
** }
** #  define LOG_DEBUG(STR, ...) {\
** 	int fd__ = open(DEBUG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0644);\
** 	dprintf(fd__, "%-40.40s:%3i [\e[34;1mDEBUG\e[0m]: ", __FILE__, __LINE__);\
** 	dprintf(fd__, ">"STR"<\n", ##__VA_ARGS__);\
** 	close(fd__);\
** }
** # endif
*/
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>

# include "get_next_line.h"
# include "ctypeft.h"
# include "stdlibft.h"

# include "stringft.h"
# include "xstring.h"

# include "stdioft.h"
# include "xstdio.h"

# include "vector.h"

#endif
