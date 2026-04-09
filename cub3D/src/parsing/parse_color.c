/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:02:33 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/09 19:12:23 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	parse_color_value(char *str, t_color *color)
{
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split)
		error_exit("Malloc failed", NULL);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		free_split(split);
		error_exit("Invalid RGB format", NULL);
	}
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	if (color->r < 0 || color->r > 255
		|| color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
	{
		free_split(split);
		error_exit("RGB value out of range", NULL);
	}
	free_split(split);
}

void	parse_color(t_game *game, char *line)
{
	char	*trimmed;

	game->map.floor_color = 0;
	game->map.ceiling_color = 0;
	trimmed = skip_spaces(line);
	if (!ft_strncmp(trimmed, "F ", 2))
	{
		if (game->floor_set)
			error_exit("Duplicate floor color", game);
		parse_color_value(trimmed + 2, &game->floor);
		game->map.floor_color = rgb_to_int(game->floor); // 🔥 QUI
		game->floor_set = 1;
	}
	else if (!ft_strncmp(trimmed, "C ", 2))
	{
		if (game->ceiling_set)
			error_exit("Duplicate ceiling color", game);
		parse_color_value(trimmed + 2, &game->ceiling);
		game->map.ceiling_color = rgb_to_int(game->ceiling); // 🔥 QUI
		game->ceiling_set = 1;
	}
	else
	{
		error_exit("Invalid color identifier", game);
	}
}
