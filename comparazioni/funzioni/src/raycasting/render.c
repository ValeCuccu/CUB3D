/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:21:10 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/09 13:08:20 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= 1920 || y < 0 || y >= 1080)
		return ;
	/* Calcolo dell'indirizzo di memoria del pixel (x, y)
	   questo permette al pc di interpretare anche */
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	// Scrittura del colore  
	// (Cast a unsigned int perché il colore è un int a 32 bit)
	*(unsigned int *)dest = color;
}

static void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			my_mlx_pixel_put(&game->ghost_image, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

int	render_frame(t_game *game)
{
	int		x;
	int		y;
	t_ray	ray;

	// 1. Puliamo il frame precedente
	clear_image(game);
	y = 0;
	while (y < 1920)
	{
		// 1. Inizializzazione raggio (con divisore 1920 per precisione 3D)
		init_ray(game, &ray, y); 
		set_step_and_side_dist(game, &ray);
		
		// 2. DDA e Distanza Perpendicolare
		perform_dda(game, &ray);
		
		// 3. Proiezione 3D con Soffitto/Muro/Pavimento
		draw_3d_projection(game, &ray, y);
		y++;
	}
	draw_minimap(game);
	draw_player_2d(game);
	x = 0;
	while (x < 60)
	{
		test_ray_2d(game, x); // Printa i raggi
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->window,
		game->ghost_image.img, 0, 0);
	return (0);
}
