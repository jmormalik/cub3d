/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:36:31 by jaemyu            #+#    #+#             */
/*   Updated: 2026/03/02 17:36:31 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **str)
{
	int		i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_img(t_game *game)
{
	if (game->e.img)
		mlx_destroy_image(game->mlx_ptr, game->e.img);
	if (game->w.img)
		mlx_destroy_image(game->mlx_ptr, game->w.img);
	if (game->n.img)
		mlx_destroy_image(game->mlx_ptr, game->n.img);
	if (game->s.img)
		mlx_destroy_image(game->mlx_ptr, game->s.img);
}

void	free_game(t_game *game)
{
	free(game->info.no);
	free(game->info.so);
	free(game->info.we);
	free(game->info.ea);
	free(game->info.c_tmp);
	free(game->info.f_tmp);
	free_split(game->info.map);
	free_img(game);
	if (game->mlx_image)
		mlx_destroy_image(game->mlx_ptr, game->mlx_image);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx_ptr, game->mlx_win);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}
