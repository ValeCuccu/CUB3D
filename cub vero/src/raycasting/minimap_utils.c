/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:57:21 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/01 17:18:25 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_square(t_game *game, t_vector pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(&game->ghost_image, (int)pos.x + j,
				(int)pos.y + i, color);
			j++;
		}
		i++;
	}
}
void	draw_minimap(t_game *game)
{
	int			x;
	int			y;	
	t_vector	pos;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y] && game->map.grid[y][x])
		{
			pos.x = x * 12 + 20; // 12 e' la scala giusta per una minimappa
			pos.y = y * 12 + 20; // +20 per i muri
			if (game->map.grid[y][x] == '1')
				draw_square(game, pos, 11, 0xFFFFFF);
			else if (game->map.grid[y][x] == '0'
				|| ft_strchr("NSEW", game->map.grid[y][x]))
				draw_square(game, pos, 11, 0x333333);
			x++;	
		}
		y++;
	}
}

void	draw_player_2d(t_game *game)
{
	t_vector	p_pos;
	int			p_size;

	p_size = 6;
	// 1. Traduzione coordinate MAPPA -> PIXEL
	p_pos.x = (game->player.pos.x * 12) + 20;
	p_pos.y = (game->player.pos.y * 12) + 20;
	// 2. Centratura del puntino
	p_pos.x -= (p_size / 2);
	p_pos.y -= (p_size / 2);
	draw_square(game, p_pos, p_size, 0xFF0000);
}
