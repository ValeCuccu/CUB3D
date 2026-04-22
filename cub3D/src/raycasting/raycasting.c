/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:55:21 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/22 10:06:49 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	draw_fc_pixel(t_game *g, t_point p, t_vector *f, int is_fl)
{
	int		t_x;
	int		t_y;
	t_img	*tex;

	if (is_fl)
		tex = &g->textures.f_tex;
	else
		tex = &g->textures.c_tex;
	if (tex->width <= 0 || tex->height <= 0)
		return ;
	t_x = (int)(f->x * tex->width) % tex->width;
	t_y = (int)(f->y * tex->height) % tex->height;
	if (t_x < 0)
		t_x += tex->width;
	if (t_y < 0)
		t_y += tex->height;
	my_mlx_pixel_put(&g->ghost_image, p.x, p.y,
		get_texture_pixel(tex, t_x, t_y));
}

static void	draw_ceil_and_floor(t_game *g, t_ray *r, int x, int *b)
{
	t_point		p;
	double		w;
	double		pr;
	t_vector	f;
	t_vector	hit;

	hit.x = g->player.pos.x + r->perp_wall_dist * r->ray_dir_x;
	hit.y = g->player.pos.y + r->perp_wall_dist * r->ray_dir_y;
	p.x = x;
	p.y = -1;
	while (++p.y < WIN_HEIGHT)
	{
		if (p.y >= b[1] && p.y <= b[2])
			continue ;
		pr = p.y - WIN_HEIGHT / 2.0;
		if (pr == 0.0)
			pr = 1.0;
		w = ((0.5 * WIN_HEIGHT) / fabs(pr)) / r->perp_wall_dist;
		f.x = w * hit.x + (1.0 - w) * g->player.pos.x;
		f.y = w * hit.y + (1.0 - w) * g->player.pos.y;
		draw_fc_pixel(g, p, &f, p.y > b[2]);
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
	draw_ceil_and_floor(game, ray, x, bounds);
	draw_column_pixels(game, ray, x, bounds);
}