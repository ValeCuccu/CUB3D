/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:43:56 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/23 10:49:16 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

static void	draw_ceil_and_floor(t_game *game, int x, int start, int end)
{
	int	y;

	y = 0;
	while (y < start)
	{
		my_mlx_pixel_put(&game->ghost_image, x, y, game->map.ceiling_color);
		y++;
	}
	y = end;
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&game->ghost_image, x, y, game->map.floor_color);
		y++;
	}
}

static void	draw_column_pixels(t_game *g, t_ray *r, int x, int *bounds)
{
	t_img	*t;
	double	step;
	double	t_pos;
	int		t_y;
	int		t_x;

	t = get_wall_texture(g, r);
	t_x = calculate_tex_x(g, r, t);
	step = 1.0 * t->height / bounds[0];
	t_pos = (bounds[1] - WIN_HEIGHT / 2 + bounds[0] / 2) * step;
	while (bounds[1] < bounds[2])
	{
		t_y = (int)t_pos;
		if (t_y >= t->height)
			t_y = t->height - 1;
		if (t_y < 0)
			t_y = 0;
		t_pos += step;
		my_mlx_pixel_put(&g->ghost_image, x, bounds[1],
			get_texture_pixel(t, t_x, t_y));
		bounds[1]++;
	}
}

void	draw_3d_projection(t_game *game, t_ray *ray, int x)
{
	int	bounds[3];

	bounds[0] = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	bounds[1] = -bounds[0] / 2 + WIN_HEIGHT / 2;
	if (bounds[1] < 0)
		bounds[1] = 0;
	bounds[2] = bounds[0] / 2 + WIN_HEIGHT / 2;
	if (bounds[2] >= WIN_HEIGHT)
		bounds[2] = WIN_HEIGHT - 1;
	draw_ceil_and_floor(game, x, bounds[1], bounds[2]);
	draw_column_pixels(game, ray, x, bounds);
}
