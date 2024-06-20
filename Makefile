NAME = philo

CFLAGS = -Wall -Werror -Wextra
CC = cc -g
RM = rm -rf

SRC_DIR = src


SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "compiling..."
	@$(CC) $(CFLAGS) -pthread $(OBJS) -o $(NAME)  > /dev/null
	@echo "\033[0;32mCompilation Finished\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@  > /dev/null

clean:
	@$(RM) $(SRC_DIR)/*.o


fclean: clean
	@$(RM) $(NAME)


re: fclean all
