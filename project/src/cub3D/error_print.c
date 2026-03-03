/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:38:20 by jaemyu            #+#    #+#             */
/*   Updated: 2026/03/02 17:38:20 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_print(char *msg)
{
	if (write(2, "Error\n", 6) < 0)
		perror(NULL);
	if (write(2, msg, ft_strlen(msg)) < 0)
		perror(NULL);
}