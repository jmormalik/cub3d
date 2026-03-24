/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 12:08:45 by jaemyu            #+#    #+#             */
/*   Updated: 2026/03/03 12:08:45 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	player_coordinate_init(t_game *game, char map, int x, int y)
{
	const int	arr[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
	int			i;

	i = -1;
	if (map == 'N')
		i = 0;
	else if (map == 'E')
		i = 1;
	else if (map == 'S')
		i = 2;
	else if (map == 'W')
		i = 3;
	game->player.dir_x = arr[i][0];
	game->player.dir_y = arr[i][1];
	game->player.player_x = x + 0.5;
	game->player.player_y = y + 0.5;
	game->player.plane_x = arr[(i + 1) % 4][0] * 0.66;
	game->player.plane_y = arr[(i + 1) % 4][1] * 0.66;
	return (1);
}

static int	map_form_check(t_game *game, char **map)
{
	int		x;
	int		y;
	int		p_c;

	y = -1;
	p_c = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] && map[y][x] != '\n')
		{
			if ((map[y][x] == '1' || map[y][x] == '0') || \
		((map[y][x] >= 9 && map[y][x] <= 13) || map[y][x] == 32))
				continue ;
			else if (map[y][x] == 'S' || map[y][x] == 'W' \
				|| map[y][x] == 'E' || map[y][x] == 'N')
			{
				p_c += player_coordinate_init(game, map[y][x], x, y);
				map[y][x] = '0';
			}
			else
				return (1);
		}
	}
	return (p_c > 1);
}

static char	**map_copy(t_game *game, char **origin)
{
	int		i;
	char	**dest;
	int		j;

	i = 0;
	while (origin[i])
		i++;
	game->info.h = i;
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (error_print("allocated error\n"), NULL);
	dest[i] = NULL;
	i = -1;
	while (origin[++i])
	{
		dest[i] = ft_calloc(sizeof(char), (game->info.w) + 1);
		if (!dest[i])
			return (free_split(dest), error_print("allocated error\n"), NULL);
		ft_memcpy(dest[i], origin[i], ft_strlen(origin[i]));
		j = -1;
		while (++j < game->info.w)
			if (!dest[i][j] || dest[i][j] == '\n')
				dest[i][j] = ' ';
	}
	return (dest);
}

static int	map_coordinate_check(char **tmp_map, size_t x, size_t y)
{
	if (x < 0 || y < 0 || !tmp_map[y] || !tmp_map[y][x] || \
		tmp_map[y][x] == ' ' || tmp_map[y][x] == '\n' || !tmp_map[y][x])
		return (1);
	if (tmp_map[y][x] == '1')
		return (0);
	if (!x)
		return (1);
	tmp_map[y][x] = '1';
	if (map_coordinate_check(tmp_map, x + 1, y))
		return (1);
	if (map_coordinate_check(tmp_map, x - 1, y))
		return (1);
	if (tmp_map[y + 1] && ft_strlen(tmp_map[y + 1]) <= x)
		return (1);
	if (map_coordinate_check(tmp_map, x, y + 1))
		return (1);
	if (y > 0 && ft_strlen(tmp_map[y - 1]) <= x)
		return (1);
	if (map_coordinate_check(tmp_map, x, y - 1))
		return (1);
	return (0);
}

int	map_valid_check(t_game *game)
{
	char	**tmp_map;
	char	**copy_map;
	int		x;
	int		y;

	tmp_map = game->info.map + game->info.h;
	if (map_form_check(game, tmp_map))
		return (error_print("Invalid map format\n"), 1);
	copy_map = map_copy(game, tmp_map);
	if (!copy_map)
		return (1);
	y = -1;
	while (tmp_map[++y])
	{
		x = -1;
		while (tmp_map[y][++x])
		{
			if ((tmp_map[y][x] == '0') && map_coordinate_check(tmp_map, x, y))
				return (error_print("Invalid map format\n"), \
				free_split(copy_map), 1);
		}
	}
	free_split(game->info.map);
	game->info.map = copy_map;
	return (0);
}
