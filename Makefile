NAME =			cub3D

SRC_PATH =		sources
UTL_PATH =		sources/utils
INC_PATH =		includes
LIB_PATH =		libraries
LFT_PATH =		$(LIB_PATH)/libft
OBJ_DIR  =		objects

SRC =	main.c \
		$(SRC_PATH)/render.c \
		$(SRC_PATH)/map.c

OSRC  = 	$(SRC:%.c=$(OBJ_DIR)/%.o)
MLX   =		$(MLX_PATH)/libmlx.a
LIBFT = 	$(LFT_PATH)/libft.a
INCLUDES = 	$(INC_PATH)/cub3d.h


CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./includes #-g -fsanitize=thread

ifeq ($(shell uname),Darwin)
 MLX_PATH = $(LIB_PATH)/Minilibx
 MLX_FLAGS = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
else
 MLX_PATH = $(LIB_PATH)/Minilibx_l
 MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm
endif

all: $(NAME)

$(NAME): $(OSRC) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) ${OSRC} $(LIBFT) -I$(MLX_PATH) $(MLX_FLAGS) -o $(NAME)
	@echo "cub3D created"

$(LIBFT):
	@make -C $(LFT_PATH)

$(MLX):
	@make -C $(MLX_PATH)

ex: re
	@./cub3D

$(OBJ_DIR)/%.o: %.c #$(INCLUDES)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LFT_PATH)
	@make clean -C $(MLX_PATH)
	@echo "Object files cleaned"

fclean: clean
	@rm -rf $(NAME)
	make fclean -C $(LFT_PATH)
	@echo "Executable and libraries cleaned"

re: fclean all

.PHONY: all clean fclean re ex