NAME = philo
SRC = main.c thread.c message.c utility.c
FLG = -Wall -Werror -Wextra #-fsanitize=address -g3

all:	$(NAME)

$(NAME):
		gcc $(FLG) -pthread $(SRC) -o $(NAME)

clean:
		rm -f $(NAME)

fclean: clean

norm:
	@norminette

re:		fclean all
