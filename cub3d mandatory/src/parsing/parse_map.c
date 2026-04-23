/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:57:27 by anpastac          #+#    #+#             */
/*   Updated: 2026/04/14 11:44:49 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	**resize_map(t_game *game, char **old, int new_size)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (new_size + 1));
	if (!new)
		error_exit("Malloc failed", game);
	i = 0;
	while (old && old[i])
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
	new_grid = resize_map(game, game->map.grid, game->map.height + 1);
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
	add_map_line(game, clean);
	free(clean);
}
