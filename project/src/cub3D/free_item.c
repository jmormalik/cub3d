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

void	free_game(t_game *game)
{
	free(game->info.no);
	free(game->info.so);
	free(game->info.we);
	free(game->info.ea);
	free(game->info.c_tmp);
	free(game->info.f_tmp);
	free_split(game->info.map);
}