NAME = bin/cub3d

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = \
	main.c map.c path_control.c \
	utils.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CC = gcc

$(shell mkdir -p bin $(OBJ_DIR))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -rf bin
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
