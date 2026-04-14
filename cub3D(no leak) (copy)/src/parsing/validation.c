/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:27:18 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/13 18:16:54 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Controlla se un carattere è valido nella mappa */
int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

void	handle_player(t_game *game, t_point p, char c, int *count)
{
	if (is_player(c))
	{
		(*count)++;
		game->player.pos.x = (double)p.x + 0.5;
		game->player.pos.y = (double)p.y + 0.5;
		game->player.spawn_dir = c;
	}
}

int	scan_map(t_game *game)
{
	int		y;
	int		x;
	int		player_count;
	char	c;
	t_point	p;

	y = 0;
	player_count = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y]))
		{
			c = game->map.grid[y][x];
			if (!is_valid_map_char(c)) // FIX: Ora accetta 0, 1, N, S, E, W e lo Spazio!
   				error_exit("Invalid map character", game);
			p.x = x;
			p.y = y;
			handle_player(game, p, c, &player_count);
			x++;
		}
		y++;
	}
	return (player_count);
}

int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	if (file[len - 4] == '.'
		&& file[len - 3] == 'c'
		&& file[len - 2] == 'u'
		&& file[len - 1] == 'b')
		return (1);
	return (0);
}
