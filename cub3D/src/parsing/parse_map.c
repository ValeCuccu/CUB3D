/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:11:58 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/25 13:15:27 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	**resize_map(char **old, int new_size)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (new_size + 1));
	if (!new)
		error_exit("Malloc failed", NULL);
	i = 0;
	while (i < new_size - 1)
	{
		new[i] = old[i];
		i++;
	}
	new[i] = NULL;
	free(old);
	return (new);
}

static void	add_map_line(t_game *game, char *line)
{
	char	**new_grid;

	if (!game->map.grid)
	{
		game->map.grid = malloc(sizeof(char *) * 2);
		if (!game->map.grid)
			error_exit("Malloc failed", game);
		game->map.grid[0] = ft_strdup(line);
		game->map.grid[1] = NULL;
		game->map.height = 1;
		return ;
	}
	new_grid = resize_map(game->map.grid, game->map.height + 1);
	new_grid[game->map.height] = ft_strdup(line);
	new_grid[game->map.height + 1] = NULL;
	game->map.grid = new_grid;
	game->map.height++;
}

void	parse_map(t_game *game, char *line)
{
	char	*clean;

	clean = ft_strtrim(line, "\n");
	if (!clean)
		error_exit("Malloc failed", game);
	clean = skip_spaces(clean);
	if (clean[0] == '\0')
	{
		free(clean);
		error_exit("Empty map line", game);
	}
	add_map_line(game, clean);
	free(clean);
}
