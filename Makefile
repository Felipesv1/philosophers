# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: felperei <felperei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 09:58:06 by felperei          #+#    #+#              #
#    Updated: 2024/07/10 09:58:06 by felperei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Werror -Wextra
CC = cc -g
RM = rm -rf

SRC_DIR = src
UTILS_DIR = utils


SRCS = $(wildcard $(SRC_DIR)/*.c)
UTILS = $(wildcard $(SRC_DIR)/$(UTILS_DIR)/*.c)

OBJS = $(SRCS:.c=.o) $(UTILS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "compiling..."
	@$(CC) $(CFLAGS) -pthread $(OBJS) -o $(NAME)  > /dev/null
	@echo "\033[0;32mCompilation Finished\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@  > /dev/null

clean:
	@$(RM) $(SRC_DIR)/*.o $(SRC_DIR)/$(UTILS_DIR)/*.o 


fclean: clean
	@$(RM) $(NAME)


re: fclean all
