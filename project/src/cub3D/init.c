/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 20:32:54 by jaehlee           #+#    #+#             */
/*   Updated: 2026/03/03 14:51:08 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_allo(t_game *game, int h)
{
	game->info.map = malloc(sizeof(char *) * (h + 1));
	if (!game->info.map)
		return (error_print("allocated error\n"), 1);
	game->info.map[h] = NULL;
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
	while ((line = get_next_line(fd)) != NULL)
	{
		h++;
		w = ft_strlen(line);
		if (w > game->info.w)
			game->info.w = ft_strlen(line);
		free(line);
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
}
