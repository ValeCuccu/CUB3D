/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:57:21 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/21 11:42:19 by vacuccu          ###   ########.fr       */
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
			if (pos.x + j >= 0 && pos.x + j < WIN_WIDTH
				&& pos.y + i >= 0 && pos.y + i < WIN_HEIGHT)
			{
				my_mlx_pixel_put(&game->ghost_image, (int)pos.x + j,
					(int)pos.y + i, color);
			}
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

	y = -1;
	while (game->map.grid[++y])
	{
		x = -1;
		while (game->map.grid[y][++x])
		{
			pos.x = x * MMAP_SCALE + MMAP_OFFSET;
			pos.y = y * MMAP_SCALE + MMAP_OFFSET;
			draw_square(game, pos, MMAP_SCALE, 0x000000);
			if (game->map.grid[y][x] == '1')
				draw_square(game, pos, MMAP_SCALE - 1, 0xFFFFFF);
			else if (game->map.grid[y][x] == '0'
				|| ft_strchr("NSEW", game->map.grid[y][x]))
				draw_square(game, pos, MMAP_SCALE - 1, 0x333333);
		}
	}
}

void	draw_player_2d(t_game *game)
{
	t_vector	p_pos;
	int			p_size;

	p_size = 4;
	p_pos.x = (game->player.pos.x * MMAP_SCALE) + MMAP_OFFSET;
	p_pos.y = (game->player.pos.y * MMAP_SCALE) + MMAP_OFFSET;
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

	mag = sqrt(ray->ray_dir_x * ray->ray_dir_x
			+ ray->ray_dir_y * ray->ray_dir_y);
	total_pixels = ray->perp_wall_dist * MMAP_SCALE * mag;
	start.x = (game->player.pos.x * MMAP_SCALE) + MMAP_OFFSET;
	start.y = (game->player.pos.y * MMAP_SCALE) + MMAP_OFFSET;
	i = -1;
	while (++i < (int)total_pixels)
	{
		if (start.x + (ray->ray_dir_x / mag) * i >= 0
			&& start.y + (ray->ray_dir_y / mag) * i >= 0)
		{
			my_mlx_pixel_put(&game->ghost_image,
				(int)(start.x + (ray->ray_dir_x / mag) * i),
				(int)(start.y + (ray->ray_dir_y / mag) * i), 0x00FF00);
		}
	}
}

void	perform_ray(t_game *game, int x)
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
	perform_dda(game, &ray);
	draw_ray_line_2d(game, &ray);
}
