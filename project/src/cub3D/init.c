/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 20:32:54 by jaehlee           #+#    #+#             */
/*   Updated: 2026/03/24 11:21:56 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_img(t_img *img)
{
	if (img->img)
		img->img_ptr = mlx_get_data_addr \
		(img->img, &img->bit, &img->line, &img->ed);
}

static void	mlx_img(t_game *game)
{
	game->s.img = mlx_xpm_file_to_image \
	(game->mlx_ptr, game->info.so, &game->s.img_w, &game->s.img_h);
	create_img(&(game->s));
	game->w.img = mlx_xpm_file_to_image \
	(game->mlx_ptr, game->info.we, &game->w.img_w, &game->w.img_h);
	create_img(&(game->w));
	game->e.img = mlx_xpm_file_to_image \
	(game->mlx_ptr, game->info.ea, &game->e.img_w, &game->e.img_h);
	create_img(&(game->e));
	game->n.img = mlx_xpm_file_to_image \
	(game->mlx_ptr, game->info.no, &game->n.img_w, &game->n.img_h);
	create_img(&(game->n));
}

int	init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (1);
	game->mlx_win = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "GAME");
	if (!game->mlx_win)
		return (1);
	game->mlx_image = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
	if (!game->mlx_image)
		return (1);
	mlx_img(game);
	if (!game->s.img || !game->w.img || !game->e.img ||!game->n.img)
		return (1);
	return (0);
}

int	height_init(char *path, t_game *game)
{
	int		fd;
	char	*line;
	int		h;
	int		w;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_print("fd error\n"), 1);
	h = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		h++;
		w = ft_strlen(line);
		if (w > game->info.w)
			game->info.w = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	get_next_line(-1);
	return (map_allo(game, h));
}

void	struct_init(t_game *game)
{
	game->info.map = NULL;
	game->info.ea = NULL;
	game->info.no = NULL;
	game->info.so = NULL;
	game->info.we = NULL;
	game->info.c_tmp = NULL;
	game->info.f_tmp = NULL;
	game->info.floor.r = -1;
	game->info.floor.g = -1;
	game->info.floor.b = -1;
	game->info.ceiling.r = -1;
	game->info.ceiling.g = -1;
	game->info.ceiling.b = -1;
	game->player.dir_x = -1;
	game->player.dir_y = -1;
	game->player.player_x = 0;
	game->player.player_y = 0;
	game->info.w = 0;
	game->mlx_ptr = NULL;
	game->mlx_image = NULL;
	game->mlx_win = NULL;
	game->e.img = NULL;
	game->s.img = NULL;
	game->n.img = NULL;
	game->w.img = NULL;
}
