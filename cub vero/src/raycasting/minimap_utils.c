/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:57:21 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/02 17:42:38 by vacuccu          ###   ########.fr       */
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
			pos.x = x * MMAP_SCALE + MMAP_OFFSET; // Scala aumentata a 32 per coprire meta' finestra
			pos.y = y * MMAP_SCALE + MMAP_OFFSET; // +20 per l'offset dal bordo
			if (game->map.grid[y][x] == '1')
				draw_square(game, pos, MMAP_SCALE - 1, 0xFFFFFF);
			else if (game->map.grid[y][x] == '0'
				|| ft_strchr("NSEW", game->map.grid[y][x]))
				draw_square(game, pos, MMAP_SCALE - 1, 0x333333);
			x++;	
		}
		y++;
	}
}

void	draw_player_2d(t_game *game)
{
	t_vector	p_pos;
	int			p_size;

	p_size = 4; // Dimensione del player aumentata in proporzione
	// 1. Traduzione coordinate MAPPA -> PIXEL
	p_pos.x = (game->player.pos.x * MMAP_SCALE) + MMAP_OFFSET;
	p_pos.y = (game->player.pos.y * MMAP_SCALE) + MMAP_OFFSET;
	// 2. Centratura del puntino
	p_pos.x -= (p_size / 2);
	p_pos.y -= (p_size / 2);
	draw_square(game, p_pos, p_size, 0xFF0000);
}

void	draw_ray_line_2d(t_game *game, t_ray *ray)
{
	t_vector	start;
	double		mag;
	double		total_pixels;
	int			i;

	// 1. Calcoliamo la magnitudo del vettore direzione
	mag = sqrt(ray->ray_dir_x * ray->ray_dir_x + ray->ray_dir_y * ray->ray_dir_y);
	
	// 2. Calcoliamo quanti pixel dobbiamo disegnare in totale
	// (distanza reale = perp_dist * magnitudo)
	total_pixels = ray->perp_wall_dist * MMAP_SCALE * mag;

	// 3. Punto di partenza (Pixel del giocatore)
	start.x = (game->player.pos.x * MMAP_SCALE) + MMAP_OFFSET;
	start.y = (game->player.pos.y * MMAP_SCALE) + MMAP_OFFSET;

	i = 0;
	while (i < (int)total_pixels)
	{
		// Avanziamo lungo la direzione normalizzata (diviso mag) per 1 pixel alla volta
		my_mlx_pixel_put(&game->ghost_image, 
			(int)(start.x + (ray->ray_dir_x / mag) * i), 
			(int)(start.y + (ray->ray_dir_y / mag) * i), 0x00FF00); // Verde
		i++;
	}
}

// Questa funzione prepara i dati e poi chiama la TUA perform_dda
void	test_ray_2d(t_game *game, int x)
{
	t_ray	ray;
	double	camera_x;

	camera_x = 2 * x / (double)60 - 1;
	ray.ray_dir_x = game->player.dir.x + game->player.plane.x * camera_x;
	ray.ray_dir_y = game->player.dir.y + game->player.plane.y * camera_x;
	ray.map_x = (int)game->player.pos.x;
	ray.map_y = (int)game->player.pos.y;
	ray.delta_x = fabs(1 / ray.ray_dir_x);
	ray.delta_y = fabs(1 / ray.ray_dir_y);
	ray.hit = 0;
	set_step_and_side_dist(game, &ray);
	// 2. gestione collisioni raggi con muri
	perform_dda(game, &ray);
	// 3. DISEGNO (Per vedere il risultato sulla minimappa)
	draw_ray_line_2d(game, &ray);
}
