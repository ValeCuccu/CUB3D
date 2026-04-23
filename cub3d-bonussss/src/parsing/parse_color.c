/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:57:27 by anpastac          #+#    #+#             */
/*   Updated: 2026/04/23 10:47:50 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static int	is_number(char *str)
{
	int	i;
	int	j;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			j = i;
			while (str[j] == ' ' || str[j] == '\t')
				j++;
			if (str[j] == '\0')
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static void	validate_and_fill(char **split, t_color *color, t_game *game)
{
	if (!is_number(split[0]) || !is_number(split[1])
		|| !is_number(split[2]))
	{
		free_split(split);
		error_exit("Invalid RGB value", game);
	}
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	if (color->r < 0 || color->r > 255
		|| color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
	{
		free_split(split);
		error_exit("RGB value out of range", game);
	}
	free_split(split);
}

void	parse_color_value(char *str, t_color *color, t_game *game)
{
	char	**split;
	char	*clean_str;
	int		i;

	clean_str = ft_strtrim(str, " \n\t");
	if (!clean_str)
		error_exit("Malloc failed", game);
	split = ft_split(clean_str, ',');
	free(clean_str);
	if (!split)
		error_exit("Malloc failed", game);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		free_split(split);
		error_exit("Invalid RGB format", game);
	}
	validate_and_fill(split, color, game);
}

void	parse_color(t_game *game, char *line)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (!ft_strncmp(trimmed, "F ", 2))
	{
		if (game->floor_set)
			error_exit("Duplicate floor color", game);
		parse_color_value(trimmed + 2, &game->floor, game);
		game->map.floor_color = rgb_to_int(game->floor);
		game->floor_set = 1;
	}
	else if (!ft_strncmp(trimmed, "C ", 2))
	{
		if (game->ceiling_set)
			error_exit("Duplicate ceiling color", game);
		parse_color_value(trimmed + 2, &game->ceiling, game);
		game->map.ceiling_color = rgb_to_int(game->ceiling);
		game->ceiling_set = 1;
	}
	else
		error_exit("Invalid color identifier", game);
}
