NAME	= gnline.a
CC		= cc
FLAGS	= -Wall -Werror -Wextra

SRC		= get_next_line.c get_next_line_utils.c


FINAL 	= -L. -lft

OBJ 	= $(SRC:.c=.o)

ALL 	: $(NAME)

FINAL	: $(NAME)
			$(CC) $(FINAL) 
$(NAME) : $(OBJ) 
			ar rcs $(NAME) $(OBJ)

%.o 	: %.c
			$(CC) $(FLAGS) -c $< -o $@

cc		: 
			$(CC) $(FLAGS) -c 
clean:
		$(RM) $(OBJ) $(NAME)

fclean 	: clean
			$(RM) $(NAME)

re		: fclean all

.PHONY: all clean fclean re
