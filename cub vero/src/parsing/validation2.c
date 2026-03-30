/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:40:52 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/30 17:30:00 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Controlla che ogni '0' o player non abbia spazi o caratteri invalidi attorno */
bool	check_map_8neighbors(char **map, int height, int width)
{
	int y, x;
	int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			char c = map[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				for (int i = 0; i < 8; i++)
				{
					int ny = y + dy[i];
					int nx = x + dx[i];
					if (ny < 0 || ny >= height || nx < 0 || nx >= (int)ft_strlen(map[ny]))
						return false;
					char nc = map[ny][nx];
					if (nc == ' ')
						return false;
				}
			}
		}
	}
	return true;
}

/* Controlla caratteri validi e conta il player */
static void	check_chars_and_player(t_game *game, int *p_count)
{
	int i, j;
	char c;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map.grid[i]))
		{
			c = game->map.grid[i][j];
			if (!is_valid_map_char(c))
				error_exit("Invalid map character", game);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				(*p_count)++;
				game->player.pos.x = (double)j + 0.5;
				game->player.pos.y = (double)i + 0.5;
				game->player.spawn_dir = c;
			}
			j++;
		}
		i++;
	}
}

/* Valida la mappa completa */
void	validate_map(t_game *game)
{
	int p_count = 0;

	check_chars_and_player(game, &p_count);
	if (p_count != 1)
		error_exit("Map must contain exactly one player", game);

	if (!check_map_8neighbors(game->map.grid, game->map.height, 0))
		error_exit("Map is not closed: '0' or player touches a space", game);
}