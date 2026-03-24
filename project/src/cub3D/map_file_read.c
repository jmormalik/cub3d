/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 11:39:39 by jaemyu            #+#    #+#             */
/*   Updated: 2026/02/09 11:39:39 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_allo(t_game *game, int h)
{
	game->info.map = malloc(sizeof(char *) * (h + 1));
	if (!game->info.map)
		return (error_print("allocated error\n"), 1);
	game->info.map[h] = NULL;
	return (0);
}

int	map_check(char *str)
{
	int		i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i])
		return (1);
	return (0);
}

int	map_read(char *path, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_print("fd error\n"), 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		game->info.map[i] = line;
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	get_next_line(-1);
	return (0);
}
