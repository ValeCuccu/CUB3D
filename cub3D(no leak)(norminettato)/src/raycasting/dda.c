/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:29:11 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/09 18:57:55 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
	double	camera_x;

	// Calcolo del punto sul piano della telecamera (-1 a 1)
	camera_x = 2 * x / (double)1920 - 1;
	// Direzione raggio
	ray->ray_dir_x = game->player.dir.x + game->player.plane.x * camera_x;
	ray->ray_dir_y = game->player.dir.y + game->player.plane.y * camera_x;
	ray->map_x = (int)game->player.pos.x;
	ray->map_y = (int)game->player.pos.y;
	// Calcolo delta (distanza per una cella intera)
	if (ray->ray_dir_x == 0)
		ray->delta_x = 1e30;
		// Questo raggio non incontrerà mai linee X, quindi distanza infinita
	else
		ray->delta_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
        ray->delta_y = 1e30;
    else
	{
        ray->delta_y = fabs(1 / ray->ray_dir_y);
	}
	ray->hit = 0;
}

void	set_step_and_side_dist(t_game *game, t_ray *ray)
{
	// 1. Calcolo per l'asse X
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player.pos.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->player.pos.x) * ray->delta_x;
	}
	// 2. Calcolo per l'asse Y
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player.pos.y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - game->player.pos.y) * ray->delta_y;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		// 1. Decidiamo in quale direzione saltare sulla griglia
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // Abbiamo colpito un lato Est o Ovest
		}
		else
		{
			// Saltiamo alla prossima linea Y (orizzontale)
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // Abbiamo colpito un lato Nord o Sud
		}
		// 2. Controlliamo se la nuova cella è un muro
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
		// --- CALCOLO DELLA DISTANZA PERPENDICOLARE ---
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->side_x - ray->delta_x);
		else
			ray->perp_wall_dist = (ray->side_y - ray->delta_y);
	}
}
