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

#include "../../inc/cub3d_bonus.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	check_cell(t_game *game, t_point p, int dy, int dx)
{
	int		ny;
	int		nx;
	char	nc;

	if (dy == 0 && dx == 0)
		return (1);
	ny = p.y + dy;
	nx = p.x + dx;
	if (ny < 0 || ny >= game->map.height)
		return (0);
	if (nx < 0 || nx >= (int)ft_strlen(game->map.grid[ny]))
		return (0);
	nc = game->map.grid[ny][nx];
	if (nc != '0' && nc != '1' && !is_player(nc))
		return (0);
	return (1);
}

static int	check_neighbors(t_game *game, int y, int x)
{
	int		dy;
	int		dx;
	t_point	p;

	p.x = x;
	p.y = y;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (!check_cell(game, p, dy, dx))
				return (0);
			dx++;
		}
		dy++;
	}
	return (1);
}

bool	check_map_8neighbors(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			c = game->map.grid[y][x];
			if (c == '0' || is_player(c))
			{
				if (!check_neighbors(game, y, x))
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

void	validate_map(t_game *game)
{
	int	player_count;

	player_count = scan_map(game);
	if (player_count != 1)
		error_exit("Map must contain exactly one player", game);
	if (!check_map_8neighbors(game))
		error_exit("Map is not closed", game);
}
