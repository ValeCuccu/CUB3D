/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:21:10 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/15 12:54:22 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	/* Calcolo dell'indirizzo di memoria del pixel (x, y)
	   questo permette al pc di interpretare anche */
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	// Scrittura del colore  
	// (Cast a unsigned int perché il colore è un int a 32 bit)
	*(unsigned int *)dest = color;
}

/* static void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(&game->ghost_image, x, y, 0x000000);
			x++;
		}
		y++;
	}
} */

int	render_frame(t_game *game)
{
	int		x;
	t_ray	ray;

	// Aggiorniamo la posizione del giocatore prima di calcolare i raggi
	update_player_state(game);

	// 1. Puliamo il frame precedente
	//clear_image(game);
	x = 0;
	while (x < WIN_WIDTH)
	{
		// 1. Inizializzazione raggio (con divisore per precisione 3D)
		init_ray(game, &ray, x); 
		set_step_and_side_dist(game, &ray);
		
		// 2. DDA e Distanza Perpendicolare
		perform_dda(game, &ray);
		
		// 3. Proiezione 3D con Soffitto/Muro/Pavimento
		draw_3d_projection(game, &ray, x);
		x++;
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
