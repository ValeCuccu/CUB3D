/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* raycasting.c                                       :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/04/02 17:04:33 by vacuccu           #+#    #+#             */
/* Updated: 2026/04/14 13:50:00 by vacuccu          ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_3d_projection(t_game *game, t_ray *ray, int x)
{
	int	line_h;
	int	draw_start;
	int	draw_end;
	int	y;

	// 1. Calcolo altezza muro basato sulla distanza perpendicolare
	line_h = (int)(WIN_HEIGHT / ray->perp_wall_dist);

	// 2. Calcolo dei limiti del muro (centratura verticale)
	draw_start = -line_h / 2 + WIN_HEIGHT / 2;
	draw_end = line_h / 2 + WIN_HEIGHT / 2;

	// 3. Disegno della colonna verticale completa
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y < draw_start && y >= 0) // Zona Soffitto
			my_mlx_pixel_put(&game->ghost_image, x, y, game->map.ceiling_color);
		else if (y >= draw_start && y <= draw_end) // Zona Muro
		{
			// Per ora usiamo un colore diverso in base al lato colpito 
			if (ray->side == 1)
				my_mlx_pixel_put(&game->ghost_image, x, y, 0xAAAAAA);
			else
				my_mlx_pixel_put(&game->ghost_image, x, y, 0xFFFFFF);
		}
		else if (y > draw_end && y < WIN_HEIGHT) // Zona Pavimento
			my_mlx_pixel_put(&game->ghost_image, x, y, game->map.floor_color);
		y++;
	}
}