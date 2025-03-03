Name = so_long
libs = -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit

srs = main.c \
	  libft/get_next_line.c \
	  libft/get_next_line_utils.c

objcts = $(src : .c = .o)

all : $(NAME)

$(NAME) : 