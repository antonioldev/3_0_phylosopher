NAME	=	philo_bonus
CC		=	cc
DEPS	=	philo_bonus.h
FLAGS	=	-Wall -Wextra -Werror -g3
SRC		=	main.c initiate.c dinner.c action.c utils.c
OBJ		=	$(SRC:.c=.o)
RM		=	rm -f

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o		:	%.c
			$(CC) $(FLAGS) -c -o $@ $<

clean	:
			$(RM) $(OBJ)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	: all clean fclean re