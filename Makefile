NAME = bin/cub3d

LIB_DIR = lib
LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = lib/mlx
MLX = $(MLX_DIR)/libmlx.a
LDFLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

SRC = main.c map.c path_control.c utils.c map_utils.c map_data_control.c \
		mlx_initialize.c raycasting.c draw.c movement.c texture.c \
		set_ray_coordinate.c init_ray.c map_copy.c map_control.c \
		ft_dispose.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CC = gcc

$(shell mkdir -p bin $(OBJ_DIR) )

all: $(NAME) run

$(NAME): $(MLX) $(OBJ) $(LIBFT) 
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	curl -O https://cdn.intra.42.fr/document/document/18344/minilibx_opengl.tgz
	tar -xvf minilibx_opengl.tgz -C $(LIB_DIR)
	mv lib/minilibx_opengl* lib/mlx
	rm -f minilibx_opengl.tgz
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	rm -rf $(MLX_DIR)

re: fclean all

run:
	@./$(NAME) maps/sa.cub
.PHONY: all clean fclean re
