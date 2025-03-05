Name = so_long

libs =  -Llibft -lft -Lminilibx -lmlx -framework OpenGL -framework AppKit
INCLUDES = -I includes

cc = cc
cflags = -Wall -Werror -Wextra 

srs = main.c  parse.c  libft/get_next_line.c \
	  libft/get_next_line_utils.c

objcts = $(srs:.c=.o)

all : $(Name)

$(Name) : $(objcts)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c  includes/so_long.h includes/get_next_line.h	
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	rm -rf $(objcts)

fclean :clean
	rm -rf $(Name)

re :fclean all

.PHONY : clean
