CC = cc -c -Wall -Wextra -Werror -g
NAME = cub3D.a

INC = -I ../../include -I ../../../minilibx-linux
LIB = ../../library

SRCS = \
main.c map_file_read.c init.c error_print.c free_item.c map_file_read.c map_info_parse.c \
utils.c valid_map_check.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $^ -o $@ $(INC)

$(NAME): $(OBJS)
	@mkdir -p ../../library
	@ar -rcs $(LIB)/$(NAME) $^

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(LIB)/$(NAME)

re: fclean all

.PHONY: all clean fclean re
