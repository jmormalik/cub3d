/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 13:20:11 by jaemyu            #+#    #+#             */
/*   Updated: 2026/03/02 13:20:11 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_parse(t_color *color, char *target)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_split(target, ',');
	if (!str)
		return (1);
	while (str[i])
		i++;
	if (i != 3)
		return (free_split(str), 1);
	color->r = cub_atoi(str[0]);
	color->g = cub_atoi(str[1]);
	color->b = cub_atoi(str[2]);
	free_split(str);
	if (color->r < 0 || color->g < 0 || color->b < 0)
		return (1);
	return (0);
}

static char	*data_extraction(char *target)
{
	char	*ret;
	char	*start_str;
	int		len;
	int		i;

	i = 0;
	start_str = target;
	while ((start_str[i] >= 9 && start_str[i] <= 13) || start_str[i] == 32)
		i++;
	if (start_str[i] == '\n' || start_str[i] == '\0')
		return (error_print("empty argument\n"), NULL);
	len = i;
	while (start_str[len] && start_str[len] != '\n')
		len++;
	while (len > i && (target[len - 1] == '\r' || target[len - 1] == ' '))
		len--;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (error_print("allocated error\n"), NULL);
	ft_memmove(ret, start_str + i, len);
	ret[len - i] = '\0';
	return (ret);
}

static int	parse_check(char *line, char **dst, char *search, int *checker)
{
	size_t	len;

	len = ft_strlen(search);
	if (ft_strncmp(line, search, len) != 0)
		return (0);
	*checker = 1;
	if (*dst)
		return (error_print("duplicated argument\n"), 1);
	*dst = data_extraction(line + len);
	if (!*dst)
		return (1);
	return (0);
}

static int	data_find_sup(t_game *game, int i, int *checker)
{
	if (parse_check(game->info.map[i], \
		&game->info.no, "NO ", checker))
		return (1);
	else if (parse_check(game->info.map[i], \
		&game->info.so, "SO ", checker))
		return (1);
	else if (parse_check(game->info.map[i], \
		&game->info.we, "WE ", checker))
		return (1);
	else if (parse_check(game->info.map[i], \
		&game->info.ea, "EA ", checker))
		return (1);
	else if (parse_check(game->info.map[i], \
		&game->info.c_tmp, "C ", checker))
		return (1);
	else if (parse_check(game->info.map[i], \
		&game->info.f_tmp, "F ", checker))
		return (1);
	return (0);
}

int	data_find(t_game *game)
{
	int		i;
	int		checker;

	i = 0;
	checker = 0;
	while (game->info.map[i])
	{
		if (data_find_sup(game, i, &checker))
			return (1);
		if (!checker && map_check(game->info.map[i]))
			break ;
		checker = 0;
		i++;
	}
	if (!game->info.no || !game->info.so || !game->info.we || \
		!game->info.ea || !game->info.c_tmp || !game->info.f_tmp)
		return (error_print("not enough argument\n"), 1);
	return (game->info.h = i, 0);
}
