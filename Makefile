# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    check_norris_loves_the_norminette.c                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chuck <chuck@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2042/02/30 42:00:00 by chuck             #+#    #+#              #
#    Updated: 2042/02/30 41:59:59 by chuck            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re log

NAME		= gbmu

CC			= gcc
CC_FLAGS	= -Wall -Wextra -Werror -g
CC_HEADERS	= -I incs

LIB_PATH	= ./libft
LIB_NAME	= ./libft/libft.a
LIB_INCS	= -I $(LIB_PATH)/incs
LIB_LD		= -L $(LIB_PATH) -lft

SDL_INCS    = -I/Users/lchenut/.brew/include/SDL2 -D_THREAD_SAFE
SDL_LD      = -L/Users/lchenut/.brew/lib -lSDL2 -lSDL2_ttf

C_DIR		= srcs
H_DIR		= incs
O_DIR		= objs

include Makefile_cfg.mk

O_DIRS		= $(C_DIRS:$(C_DIR)%=$(O_DIR)%)
O_FILES		= $(C_FILES:$(C_DIR)%.c=$(O_DIR)%.o)

all:
	make -C $(LIB_PATH)
	make $(NAME)

$(NAME):		$(O_FILES) $(LIB_NAME)
	$(CC) $^ -o $@ $(LIB_LD) $(SDL_LD)

$(O_DIR)/%.o:	$(C_DIR)/%.c $(H_FILES)
	@mkdir -p $(O_DIRS) $(O_DIR)
	$(CC) $(CC_FLAGS) $(CC_HEADERS) $(LIB_INCS) $(SDL_INCS) -o $@ -c $<

clean:
	@rm -rf $(O_DIR)

fclean: clean
	@rm -rf $(NAME)

check:
	make -k -C tests/unit

log:
	touch /tmp/.debug_irc; clear; tail -f /tmp/.debug_irc

config:
	@echo "C_FILES="$$(find srcs -name '*.c' -type f) > Makefile_cfg.mk
	@echo "C_DIRS="$$(find srcs -type d -follow -print) >> Makefile_cfg.mk
	@echo "H_FILES="$$(find incs -name '*.h' -type f) >> Makefile_cfg.mk

re: fclean all
