NAME =			cub3D

SRC_PATH =		sources
INI_PATH =		sources/init
MOV_PATH =		sources/move
DRW_PATH =		sources/draw
RND_PATH =		sources/render
INC_PATH =		includes
LIB_PATH =		libraries
LFT_PATH =		libraries/libft
OBJ_DIR  =		objects

SRC =	cub3D.c \
		$(MOV_PATH)/keys.c \
		$(MOV_PATH)/move_player.c \
		$(MOV_PATH)/rotate.c \
		$(DRW_PATH)/draw_map.c \
		$(DRW_PATH)/draw_player.c \
		$(DRW_PATH)/draw_utils.c \
		$(RND_PATH)/render_frames.c \
		$(RND_PATH)/render.c \
		$(RND_PATH)/render_utils.c \
		$(INI_PATH)/data_init.c \
		$(INI_PATH)/map_init.c \
		$(INI_PATH)/parser.c \
		$(INI_PATH)/map_validator.c \
		$(INI_PATH)/file_validator.c \
		$(INI_PATH)/identifiers_check.c \
		$(INI_PATH)/map_structure_check.c \
		$(INI_PATH)/texture_set.c \
		$(INI_PATH)/colour_set.c \
		$(SRC_PATH)/allocator.c \
		$(SRC_PATH)/general_utils.c \
		$(SRC_PATH)/doors/doors.c \
		$(SRC_PATH)/doors/doors_anim.c \
		$(SRC_PATH)/doors/doors_init.c


OSRC  = 	$(SRC:%.c=$(OBJ_DIR)/%.o)
MLX   =		$(MLX_PATH)/libmlx.a
LIBFT = 	$(LFT_PATH)/libft.a
INCLUDES = 	$(INC_PATH)/cub3d.h


CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./includes -g #-fsanitize=thread

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
	@echo "Libft created"
	@make -C $(LFT_PATH)

$(MLX):
	@echo "MLX created"
	@make -C $(MLX_PATH)

$(OBJ_DIR)/%.o: %.c $(INCLUDES) Makefile
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LFT_PATH)
	@make clean -C $(MLX_PATH)
	@echo "Object files cleaned"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LFT_PATH)
	@echo "Executable and libraries cleaned"

re: fclean all

.PHONY: all clean fclean re
