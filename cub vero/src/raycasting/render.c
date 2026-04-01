/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:21:10 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/01 13:13:27 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	render_frame(t_game *game)
{
	int			x;
	double		camerax;
	t_vector	ray_dir;

	x = 0;
	while (x < 1920)
	{
		camerax = 2 * x / (double)1920 - 1;
		ray_dir.x = game->player.dir.x + game->player.plane.x * camerax;
		ray_dir.y = game->player.dir.y + game->player.plane.y * camerax;
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->ghost_image.img, 0, 0);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= 1920 || y < 0 || y >= 1080)
		return ;
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dest = color;
}

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;
	int	color;
	int	i;
	int	j;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			//bianco per i muri
			if (game->map.grid[y][x] == '1')
				color = 0xFFFFFF;
			else
				color = 0x555555; //grigio per il resto
			i = 0;
			while (i < TILE_SIZE)
			{
				j = 0;
				while (j < TILE_SIZE)
					my_mlx_pixel_put(&game->ghost_image, x * TILE_SIZE, game->player.pos.y * TILE_SIZE, 0xFFFF00); //giocatore giallo
			}
		}
	}
}
