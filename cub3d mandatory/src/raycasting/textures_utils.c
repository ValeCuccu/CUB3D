/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:53:36 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/15 14:54:51 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_texture_pixel(t_img *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_length
			+ x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

t_img	*get_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->textures.e_tex);
		return (&game->textures.w_tex);
	}
	if (ray->ray_dir_y > 0)
		return (&game->textures.s_tex);
	return (&game->textures.n_tex);
}

int	calculate_tex_x(t_game *game, t_ray *ray, t_img *tex)
{
	double	wall_hit_x;
	int		tex_x;

	if (ray->side == 0)
		wall_hit_x = game->player.pos.y + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		wall_hit_x = game->player.pos.x + ray->perp_wall_dist
			* ray->ray_dir_x;
	wall_hit_x -= floor(wall_hit_x);
	tex_x = (int)(wall_hit_x * (double)tex->width);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
