/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:40:52 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/25 16:05:35 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	setup_map_dimension(t_game *game)
{
	int	i;
	int	len;

	i = 0;
	game->map.width = 0;
	while (i < game->map.height)
	{
		len = ft_strlen(game->map.grid[i]);
		if (len > game->map.width)
			game->map.width = len;
		i++;
	}
	i = 0;
	while (i < game->map.height)
	{
		pad_row(&game->map.grid[i], game->map.width);
		i++;
	}
}

static void	check_chars_and_player(t_game *game, int *p_count)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
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
		}
	}
}

void	validate_map(t_game *game)
{
	int	p_count;
	int	i;
	int	j;

	p_count = 0;
	setup_map_dimension(game);
	check_chars_and_player(game, &p_count);
	if (p_count != 1)
		error_exit("Map must contain exactly one player", game);
	i = 0;
	while (++i < game->map.height -1)
	{
		j = 0;
		while (++j < game->map.width -1)
		{
			if (game->map.grid[i][j] == ' ')
				error_exit("Invalid space inside map", game);
		}
	}
	check_borders(game);
}
