/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 17:04:33 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/09 13:32:57 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_mock_colors(t_game *game)
{
    // Colori in formato esadecimale: 0xRRGGBB
    
    // Per il soffitto proviamo un azzurro cielo
    game->map.ceiling_color = 0x0000FF; 
    
    // Per il pavimento proviamo un grigio scuro o marrone
    game->map.floor_color = 0xFFFF00; 
}

void	draw_3d_projection(t_game *game, t_ray *ray, int x)
{
	int	line_h;
	int	draw_start;
	int	draw_end;
	int	y;

	// 1. Calcolo altezza muro basato sulla distanza perpendicolare
	line_h = (int)(1080 / ray->perp_wall_dist);

	// 2. Calcolo dei limiti del muro (centratura verticale)
	draw_start = -line_h / 2 + 1080 / 2;
	draw_end = line_h / 2 + 1080 / 2;

	// 3. Disegno della colonna verticale completa
	y = 0;
	while (y < 1080)
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
		else if (y > draw_end && y < 1080) // Zona Pavimento
			my_mlx_pixel_put(&game->ghost_image, x, y, game->map.floor_color);
		y++;
	}
}
