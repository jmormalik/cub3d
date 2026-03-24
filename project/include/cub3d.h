/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:22:13 by jaemyu            #+#    #+#             */
/*   Updated: 2026/03/24 11:22:13 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
# include <math.h>

# define HEIGHT 480
# define WIDTH	960
# define TEX_WIDTH 64

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
}	t_color;

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

typedef struct s_player
{
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}	t_player;

typedef struct s_img
{
	void	*img;
	void	*img_ptr;
	int		bit;
	int		line;
	int		ed;
	int		x;
	int		y;
	int		draw_x;
	int		draw_y;
	int		img_w;
	int		img_h;
}	t_img;

typedef struct s_ray
{
	double			ray_x;
	double			ray_y;
	int				mapx;
	int				mapy;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	double			lineheight;
	double			drawstart;
	double			drawend;
	unsigned int	*offset;
	char			*img_addr;
	int				hit_side;
	int				tex_x;
	t_img			*cur_tex;
	double			step;
	double			tex_pos;
}	t_ray;

typedef struct s_game
{
	t_map		info;
	t_player	player;
	t_img		w;
	t_img		n;
	t_img		e;
	t_img		s;
	t_ray		ray;
	int			update_flag;
	void		*mlx_ptr;
	void		*mlx_win;
	void		*mlx_image;
}	t_game;

//init
int		height_init(char *path, t_game *game);
void	struct_init(t_game *game);
int		init_mlx(t_game *game);
//map_file_read
int		map_allo(t_game *game, int h);
int		map_check(char *str);
int		map_read(char *path, t_game *game);
//map_info_parse
int		rgb_parse(t_color *color, char *target);
int		data_find(t_game *game);
//utils
int		cub_atoi(const char *nptr);
int		ft_close(void *game);
//error_print
void	error_print(char *msg);
//free_item
void	free_split(char **str);
void	free_game(t_game *game);
//valid_map_check
int		map_valid_check(t_game *game);
//event
int		ft_key_press(int keycode, void *param);
//raycast
void	rayloop(t_game *game);
//rendering
void	get_wall_dir(t_game *game, int side);

#endif