NAME = philo
SRC = main.c thread.c message.c philo_utility.c utility.c
FLG = -Wall -Werror -Wextra #-fsanitize=address -g3

all:	$(NAME)

$(NAME):
		gcc $(FLG) -pthread $(SRC) -o $(NAME)

clean:
		rm -f $(NAME)

fclean: clean

re:		fclean all
