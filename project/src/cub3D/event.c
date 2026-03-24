/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 17:16:10 by jaemyu            #+#    #+#             */
/*   Updated: 2026/03/21 17:16:10 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_lr(t_game *game, int sign)
{
	float	oldx;
	float	speed;

	speed = sign * 0.07;
	oldx = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * \
	cos(speed) - game->player.dir_y * sin(speed);
	game->player.dir_y = game->player.dir_y * \
	cos(speed) + oldx * sin(speed);
	oldx = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * \
	cos(speed) - game->player.plane_y * sin(speed);
	game->player.plane_y = game->player.plane_y * \
	cos(speed) + oldx * sin(speed);
}

int	is_empty(t_game *game, double newx, double newy, double r)
{
	int		p_mapx;
	int		p_mapy;
	int		m_mapx;
	int		m_mapy;

	p_mapx = newx + r;
	p_mapy = newy + r;
	m_mapx = newx - r;
	m_mapy = newy - r;
	return (\
		game->info.map[p_mapy][p_mapx] == '0' && \
		game->info.map[p_mapy][m_mapx] == '0' && \
		game->info.map[m_mapy][m_mapx] == '0' && \
		game->info.map[m_mapy][p_mapx] == '0' \
	);
}

void	move_wasd(t_game *game, double x, double y)
{
	double	newx;
	double	newy;

	newx = game->player.player_x + x;
	newy = game->player.player_y + y;
	if (is_empty(game, newx, newy, 0.2))
	{
		game->player.player_x = newx;
		game->player.player_y = newy;
	}
	else if (is_empty(game, newx, game->player.player_y, 0.2))
		game->player.player_x = newx;
	else if (is_empty(game, game->player.player_x, newy, 0.2))
		game->player.player_y = newy;
}

int	ft_key_press(int keycode, void *param)
{
	t_game	*game;

	game = param;
	if (keycode == KEY_W)
		move_wasd(game, game->player.dir_x / 10, game->player.dir_y / 10);
	else if (keycode == KEY_A)
		move_wasd(game, -game->player.plane_x / \
			0.66 / 10, -game->player.plane_y / 0.66 / 10);
	else if (keycode == KEY_S)
		move_wasd(game, -game->player.dir_x / 10, -game->player.dir_y / 10);
	else if (keycode == KEY_D)
		move_wasd(game, game->player.plane_x / 0.66 / \
			10, game->player.plane_y / 0.66 / 10);
	else if (keycode == KEY_LEFT)
		move_lr(game, -1);
	else if (keycode == KEY_RIGHT)
		move_lr(game, 1);
	else if (keycode == KEY_ESC)
		ft_close(game);
	if (keycode != KEY_ESC)
		game->update_flag = 1;
	return (0);
}
