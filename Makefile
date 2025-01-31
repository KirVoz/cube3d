SRC =	main.c \
		./src/dda.c \
		./src/render.c \
		./src/map.c \

OBJS = $(SRC:.c=.o)

HEAD = cube3d.h

NAME = cube3d

MAKE_MLX = cd ./libraries/Minilibx/ && make

MAKE_LIB = cd ./libraries/libft/ && make

CC = cc

CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address

RM = rm -rf

LIBFT = ft

LIBFT_DIR = libft

MACOS = -framework OpenGL -framework AppKit

LINUX = -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE_MLX)
	@$(MAKE_LIB)
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $(OBJS) ./libraries/libft/libft.a ./libraries/Minilibx/libmlx.a $(MACOS) -o $(NAME)
	@echo "Completed! 🤠"
	
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C ./libraries/libft
	@$(MAKE) clean -C ./libraries/Minilibx
	@echo "Completed! 😈"
	
clean:
	@$(RM) $(NAME)
	@$(MAKE) clean -C ./libraries/libft
	@$(RM) -rf ./libraries/libft/libft.a
	@rm -f ${OBJS}

re:	fclean all

.PHONY: all clean fclean re