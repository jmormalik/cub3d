/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 09:39:25 by jaemyu            #+#    #+#             */
/*   Updated: 2026/03/23 09:39:25 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_wallx(t_game *game, int side, t_img dir)
{
	double	wallx;

	if (side == 0)
		wallx = game->player.player_y + \
		game->ray.perp_wall_dist * game->ray.ray_y;
	else
		wallx = game->player.player_x + \
		game->ray.perp_wall_dist * game->ray.ray_x;
	wallx -= floor(wallx);
	game->ray.tex_x = (int)(wallx * (double)dir.img_w);
	if (side == 0 && game->ray.ray_x > 0)
		game->ray.tex_x = dir.img_w - game->ray.tex_x - 1;
	if (side == 1 && game->ray.ray_y < 0)
		game->ray.tex_x = dir.img_w - game->ray.tex_x -1;
}

void	get_wall_dir(t_game *game, int side)
{
	if (side == 0 && game->ray.step_x > 0)
		game->ray.cur_tex = &game->w;
	else if (side == 0)
		game->ray.cur_tex = &game->e;
	else if (side == 1 && game->ray.step_y > 0)
		game->ray.cur_tex = &game->n;
	else
		game->ray.cur_tex = &game->s;
	game->ray.hit_side = 2 * (side == 1) \
	+ (side == 1) * (game->ray.step_y <= 0) \
	+ (side == 0) * (game->ray.step_x <= 0);
	find_wallx(game, side, *game->ray.cur_tex);
}
