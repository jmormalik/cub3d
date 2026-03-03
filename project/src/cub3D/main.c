/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:20:12 by jaemyu            #+#    #+#             */
/*   Updated: 2026/02/07 14:20:20 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	operator(char *av, t_game *game)
{
	struct_init(game);
	if (height_init(av, game))
		return (1);
	if (map_read(av, game))
		return (1);
	if (data_find(game))
		return (1);
	if (rgb_parse(&game->info.ceiling, game->info.c_tmp) || \
		rgb_parse(&game->info.floor, game->info.f_tmp))
		return (error_print("rgb value invalid\n"), 1);
	if (map_valid_check(game))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (error_print("arguments invalid\n"), 1);
	if (operator(av[1], &game))
		return (free_game(&game), 1);

	int		y = -1;
	while (game.info.map[++y])
	{
		printf("%s\n", game.info.map[y]);
	}
	return (free_game(&game), 0);
}
