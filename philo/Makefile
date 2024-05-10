# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfontenl <pfontenl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 12:47:06 by pfontenl          #+#    #+#              #
#    Updated: 2024/04/30 12:16:25 by pfontenl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

NAME=philo

FILES=	fork_utils.c \
		mutex_utils.c \
		parse_utils.c \
		philo_init.c \
		philo_thread.c \
		philo.c \
		sim_init.c \
		sim_thread.c \
		sim_utils.c \
		status_log.c \
		time_utils.c
SRC_DIR=src/
OBJ_DIR=obj/
SRC=$(addprefix $(SRC_DIR), $(FILES))
OBJ=$(addprefix $(OBJ_DIR), $(FILES:.c=.o))

HEADER=$(addprefix $(SRC_DIR), philo.h)
INCLUDE=$(HEADER) Makefile

CC=cc
CFLAGS=-Wall -Wextra -Werror

RM=rm -rf

COLOR_NONE=\033[0;0m
COLOR_RED=\033[1;31m
COLOR_GREEN=\033[1;32m
COLOR_YELLOW=\033[1;33m
COLOR_PINK=\033[1;35m
COLOR_CYAN=\033[1;36m

PREFIX=$(COLOR_YELLOW)[PHILOSOPHERS]$(COLOR_NONE)  
PREFIX_BONUS=$(COLOR_YELLOW)[PHILOSOPHERS]$(COLOR_NONE) $(COLOR_PINK)(BONUS)$(COLOR_NONE)  

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "$(PREFIX)$(COLOR_GREEN)$(NAME) generado!$(COLOR_NONE)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE)
	@mkdir -p obj/
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(PREFIX)$(COLOR_CYAN)$< compilado a $@!$(COLOR_NONE)\n"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(PREFIX)$(COLOR_RED)Objetos eliminados!$(COLOR_NONE)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(PREFIX)$(COLOR_RED)$(NAME) eliminado!$(COLOR_NONE)"

re: fclean all

.PHONY: all clean fclean re