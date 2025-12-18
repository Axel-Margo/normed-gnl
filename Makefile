NAME	= gnline.a
CC		= cc
FLAGS	= -Wall -Werror -Wextra

SRC		= get_next_line.c get_next_line_utils.c

BONUS	= get_next_line_bonus.c get_next_line_utils_bonus.c
FINAL 	= -L. -lft

OBJ 	= $(SRC:.c=.o)

ALLSRC 	= $(SRC) $(BONUS)

OBJ_ALL = $(ALLSRC:.c=.o)

ALL 	: $(NAME)

FINAL	: $(NAME)
			$(CC) $(FINAL) 
$(NAME) : $(OBJ) 
			ar rcs $(NAME) $(OBJ)

%.o 	: %.c
			$(CC) $(FLAGS) -c $< -o $@

bonus 	: $(OBJ_ALL)
	ar rcs $(NAME) $(OBJ_ALL)

cc		: 
			$(CC) $(FLAGS) -c 
clean:
		$(RM) $(OBJ_ALL) $(NAME)

fclean 	: clean
			$(RM) $(NAME)

re		: fclean all

.PHONY: all clean fclean re
