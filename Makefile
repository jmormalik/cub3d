NAME = cub3D

DIRECTORY = ./project

SOURCE = $(DIRECTORY)/src

LIBFT = $(SOURCE)/libft
CUB3D = $(SOURCE)/cub3D

LIBRARY = $(DIRECTORY)/library

CUB3D_A = $(LIBRARY)/cub3D.a
LIBFT_A = $(LIBRARY)/libft.a

CC = cc -Wall -Wextra -Werror -g
MLX_CC = -L./minilibx-linux -lmlx -lXext -lX11

MLX_DIR = ./minilibx-linux
MLX_DIR_A = $(MLX_DIR)/libmlx_Linux.a

all: $(NAME)

$(NAME): $(CUB3D_A) $(LIBFT_A) $(MLX_DIR_A)
	@$(CC) $(MLX_CC) $^ -o $@

$(MLX_DIR_A): $(MLX_DIR)
	@$(MAKE) -C $(MLX_DIR) -s
	
$(CUB3D_A): $(CUB3D)
	@$(MAKE) -C $(CUB3D) -s

$(LIBFT_A): $(LIBFT)
	@$(MAKE) -C $(LIBFT) -s
	
clean:
	@$(MAKE) -C $(MLX_DIR) clean -s
	@$(MAKE) -C $(CUB3D) fclean -s
	@$(MAKE) -C $(LIBFT) fclean -s
	
fclean: clean
	@rm -rf $(NAME)
	
re: fclean all

.PHONY: all clean fclean re bonus
