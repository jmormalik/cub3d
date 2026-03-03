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

int	map_read(char *path, t_game *game)
{                                                                                                         
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_print("fd error\n"), 1);
	while ((line = get_next_line(fd)) != NULL)
	{
		game->info.map[i] = line;
		i++;
	}
	close(fd);
	get_next_line(-1);
	return (0);
}
