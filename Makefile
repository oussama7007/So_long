
NAME = so_long
LIBS = -lmlx -framework OpenGL -framework AppKit

INCLUDES = -I includes  

CC = cc 
CFLAGS =  -Wall -Werror -Wextra

SRCS = src/main.c src/parse.c \
		src/parsing_2.c \
		src/parsing_flood_fill.c \
		src/parsing_utils.c \
		src/process_line.c \
		game/game.c \
		game/game_utils.c \
		game/game_utils1.c \
		get_next_line/get_next_line.c \
	    get_next_line/get_next_line_utils.c 

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

.PHONY: clean 