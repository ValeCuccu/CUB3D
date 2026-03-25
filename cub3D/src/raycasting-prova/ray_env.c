/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:22:00 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/25 12:29:01 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* qui calcolo la dir iniziale e la distanza da percorrere per arrivare
   al primo bordo possibile */
static void	init_ray_step(t_game *g, t_ray *r)
{
	if (g->player.dir.x < 0)
	{
		r->step_x = -1;
		r->side_x = (g->player.pos.x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - g->player.pos.x) * r->delta_x;
	}
	if (g->player.dir.y < 0)
	{
		r->step_y = -1;
		r->side_y = (g->player.pos.y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - g->player.pos.y) * r->delta_y;
	}
}

/* Calcolo il raggio per la colonna 'x' dello schermo */
static void	init_ray(t_game *g, t_ray *r, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)1024 - 1;
	r->ray_dir_x = g->player.dir.x + g->player.plane.x * camera_x;
	r->ray_dir_y = g->player.dir.y + g->player.plane.y * camera_x;
	r->map_x = (int)g->player.pos.x;
	r->map_y = (int)g->player.pos.y;
	r->delta_x = 1e30;
	if (r->ray_dir_x != 0)
		r->delta_x = fabs(1.0 / r->ray_dir_x);
	r->delta_y = 1e30;
	if (r->ray_dir_y != 0)
		r->delta_y = fabs(1.0 / r->ray_dir_y);
	init_ray_step(g, r);
}

/* L'algoritmo DDA vero e proprio: salta sui bordi finché non becca '1' */
static void	perform_dda(t_game *g, t_ray *r)
{
	r->hit = 0;
	while (r->hit == 0)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_x >= g->map.width
			|| r->map_y < 0 || r->map_y >= g->map.height)
			break ;
		if (g->map.grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

/* qui disegno il singolo raggio */
static void	draw_single_ray_2d(t_game *g, t_ray *r)
{
	double	len;
	double	steps;
	double	x;
	double	y;
	double	x_inc; // <-- NUOVE VARIABILI PER L'INCREMENTO FISSO
	double	y_inc;
	int		p[2];
	int		e[2];

	len = r->side_x - r->delta_x;
	if (r->side == 1)
		len = r->side_y - r->delta_y;
	p[0] = (int)(g->player.pos.x * TILE_SIZE);
	p[1] = (int)(g->player.pos.y * TILE_SIZE);
	e[0] = p[0] + (int)(r->ray_dir_x * len * TILE_SIZE);
	e[1] = p[1] + (int)(r->ray_dir_y * len * TILE_SIZE);
	
	steps = fabs((double)(e[0] - p[0]));
	if (fabs((double)(e[1] - p[1])) > steps)
		steps = fabs((double)(e[1] - p[1]));
        
	if (steps <= 0) // Protezione contro la divisione per zero
		return ;

	// Calcolo il passo fisso PRIMA del ciclo
	x_inc = (e[0] - p[0]) / steps;
	y_inc = (e[1] - p[1]) / steps;
	
	x = p[0];
	y = p[1];
	while (steps > 0)
	{
		my_mlx_pixel_put(&g->ghost_image, (int)x, (int)y, 0xFF0000);
		x += x_inc; // Ora avanza in modo lineare e preciso!
		y += y_inc;
		steps--;
	}
}

/* Funzione principale: chiama i calcoli e disegna la linea solida */
void	draw_ray(t_game *g)
{
	t_ray	r;
	int		x;

	x = 0;
	while (x < 1024)
	{
		init_ray(g, &r, x);
		perform_dda(g, &r);
		draw_single_ray_2d(g, &r);
		x += 16; // Disegna un raggio ogni 16 pixel (effetto ventaglio)
	}
}
