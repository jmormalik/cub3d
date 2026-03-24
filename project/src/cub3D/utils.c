/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 13:51:12 by jaemyu            #+#    #+#             */
/*   Updated: 2026/03/02 13:51:12 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub_atoi(const char *nptr)
{
	int		value;

	value = 0;
	if (!*nptr)
		return (-1);
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			return (-1);
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		value = value * 10 + (*nptr - '0');
		if (value > 255)
			return (-1);
		nptr++;
	}
	if (*nptr)
		return (-1);
	return ((int)(value));
}

int	ft_close(void *game)
{
	free_game(game);
	exit(0);
}
