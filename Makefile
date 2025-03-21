# Root Makefile

NAME = so_long
LIBS = -lmlx -framework OpenGL -framework AppKit

INCLUDES = -I includes  

CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3

SRCS = src/main.c src/parse.c  get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c game.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)  


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c  includes/so_long.h  includes/get_next_line.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS)
	

fclean: clean
	rm -rf $(NAME)


re: fclean all

.PHONY: all clean fclean re