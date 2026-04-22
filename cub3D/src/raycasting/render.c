/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:21:10 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/22 10:01:22 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

int	render_frame(t_game *game)
{
	int		x;
	t_ray	ray;

	update_player_state(game);
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game, &ray, x);
		set_step_and_side_dist(game, &ray);
		perform_dda(game, &ray);
		draw_3d_projection(game, &ray, x);
		x++;
	}
	x = 0;
	while (x < 60)
	{
		perform_ray(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->window,
		game->ghost_image.img, 0, 0);
	return (0);
}
