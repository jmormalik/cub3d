/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 15:52:34 by jaemyu            #+#    #+#             */
/*   Updated: 2026/03/22 15:52:34 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	find_wall(t_game *game)
{
	int		side;

	while (game->info.map[game->ray.mapy][game->ray.mapx] != '1')
	{
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.mapx += game->ray.step_x;
			side = 0;
		}
		else
		{
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.mapy += game->ray.step_y;
			side = 1;
		}
	}
	if (side == 0)
		game->ray.perp_wall_dist = (game->ray.mapx - game->player.player_x \
			+ (1 - game->ray.step_x) / 2.0) / game->ray.ray_x;
	else
		game->ray.perp_wall_dist = (game->ray.mapy - game->player.player_y \
			+ (1 - game->ray.step_y) / 2.0) / game->ray.ray_y;
	get_wall_dir(game, side);
}

static void	raycast(t_game *game)
{
	game->ray.delta_dist_x = 1e30;
	if (game->ray.ray_x != 0)
		game->ray.delta_dist_x = fabs(1 / game->ray.ray_x);
	game->ray.step_x = 1;
	game->ray.side_dist_x = (game->ray.mapx + 1.0 - game->player.player_x) \
	* game->ray.delta_dist_x;
	if (game->ray.ray_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist_x = (game->player.player_x - game->ray.mapx) * \
		game->ray.delta_dist_x;
	}
	game->ray.delta_dist_y = 1e30;
	if (game->ray.ray_y != 0)
		game->ray.delta_dist_y = fabs(1 / game->ray.ray_y);
	game->ray.step_y = 1;
	game->ray.side_dist_y = (game->ray.mapy + 1.0 - game->player.player_y) * \
	game->ray.delta_dist_y;
	if (game->ray.ray_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = (game->player.player_y - game->ray.mapy) * \
		game->ray.delta_dist_y;
	}
}

static int	get_tex_color(t_game *game)
{
	int		tex_y;
	int		color;
	char	*dst;

	tex_y = (int)(game->ray.tex_pos + 0.5) % game->ray.cur_tex->img_h;
	game->ray.tex_pos += game->ray.step;
	dst = (char *)(game->ray.cur_tex->img_ptr + \
		(tex_y * game->ray.cur_tex->line + game->ray.tex_x * \
		(game->ray.cur_tex->bit / 8)));
	color = *(unsigned int *)dst;
	return (color);
}

static void	color_init(t_game *game, int i)
{
	int	bit;
	int	line;
	int	ed;
	int	k;

	game->ray.step = 1.0 * game->ray.cur_tex->img_h / game->ray.lineheight;
	game->ray.tex_pos = (game->ray.drawstart - HEIGHT / 2 + \
		game->ray.lineheight / 2) * game->ray.step;
	game->ray.img_addr = mlx_get_data_addr(game->mlx_image, &bit, &line, &ed);
	k = -1;
	while (++k < HEIGHT)
	{
		game->ray.offset = (unsigned int *)(game->ray.img_addr + \
			(bit / 8) * (i + (WIDTH / 2)) + line * k);
		if (k < game->ray.drawstart)
			*game->ray.offset = game->info.ceiling.r + \
				game->info.ceiling.g + game->info.ceiling.b;
		else if (k > game->ray.drawend)
			*game->ray.offset = game->info.floor.r + \
				game->info.floor.g + game->info.floor.b;
		else
			*game->ray.offset = get_tex_color(game);
	}	
}

void	rayloop(t_game *game)
{
	int		i;

	i = -WIDTH / 2 - 1;
	while (++i < WIDTH / 2)
	{
		game->ray.ray_x = game->player.dir_x + game->player.plane_x * \
		((double)i / ((double)WIDTH / 2));
		game->ray.ray_y = game->player.dir_y + game->player.plane_y * \
		((double)i / ((double)WIDTH / 2));
		game->ray.mapx = game->player.player_x;
		game->ray.mapy = game->player.player_y;
		raycast(game);
		find_wall(game);
		game->ray.lineheight = (int)(HEIGHT / game->ray.perp_wall_dist);
		game->ray.drawstart = -game->ray.lineheight / 2 + HEIGHT / 2;
		if (game->ray.drawstart < 0)
			game->ray.drawstart = 0;
		game->ray.drawend = game->ray.lineheight / 2 + HEIGHT / 2;
		if (game->ray.drawend >= HEIGHT)
			game->ray.drawend = HEIGHT - 1;
		color_init(game, i);
	}
	mlx_put_image_to_window(game->mlx_ptr, game->mlx_win, \
		game->mlx_image, 0, 0);
	return ;
}
