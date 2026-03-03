#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/time.h>
# include <stdio.h>
# include <fcntl.h>


# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
} t_color;


typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*c_tmp;
	char	*f_tmp;
	t_color	ceiling;
	t_color	floor;
	char	**map;
	int		h;
	int		w;
}	t_map;

typedef	struct s_player
{
	float		player_x;
	float		player_y;
	float		dir_x;
	float		dir_y;
} t_player;

typedef struct s_game
{
	t_map		info;
	t_player	player;
}	t_game;

//init
int		height_init(char *path, t_game *game);
void	struct_init(t_game *game);
//map_file_read
int		map_read(char *path, t_game *game);
//map_info_parse
int	rgb_parse(t_color *color, char *target);
int	data_find(t_game *game);
//utils
int	cub_atoi(const char *nptr);
void	free_split(char **str);
//error_print
void	error_print(char *msg);
//free_item
void	free_split(char **str);
void	free_game(t_game *game);
//valid_map_check
int	map_valid_check(t_game *game);

#endif