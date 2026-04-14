/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* raycasting.c                                       :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/04/02 17:04:33 by vacuccu           #+#    #+#             */
/* Updated: 2026/04/14 13:50:00 by vacuccu          ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* ESTRAZIONE COLORE: Prende un'immagine in memoria e "legge" il colore */
static unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	char	*dst;
	int		offset;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	dst = img->addr + offset;
	return (*(unsigned int *)dst);
}

/* SELEZIONE TEXTURE: Decide quale immagine usare in base al muro colpito */
static t_img	*get_texture(t_game *g, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			return (&g->textures.e_tex);
		return (&g->textures.w_tex);
	}
	if (r->ray_dir_y > 0)
		return (&g->textures.s_tex);
	return (&g->textures.n_tex);
}

/* CALCOLO X TEXTURE: Punto esatto di impatto orizzontale ottimizzato */
static int	get_tex_x(t_game *g, t_ray *r, t_img *t)
{
	double	wall_x;
	int		tex_x;

	if (r->side == 0)
		wall_x = g->player.pos.y + r->perp_wall_dist * r->ray_dir_y;
	else
		wall_x = g->player.pos.x + r->perp_wall_dist * r->ray_dir_x;
	wall_x -= (int)wall_x;
	tex_x = (int)(wall_x * (double)t->width);
	if (r->side == 0 && r->ray_dir_x > 0)
		tex_x = t->width - tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		tex_x = t->width - tex_x - 1;
	return (tex_x);
}

/* DIMENSIONI MURO: Calcoli matematici pre-calcolati (540) per la CPU */
static void	calc_wall(t_ray *r, int *dim)
{
	if (r->perp_wall_dist < 0.0001)
		r->perp_wall_dist = 0.0001;
	dim[0] = (int)(1080 / r->perp_wall_dist);
	dim[1] = -dim[0] / 2 + 540;
	if (dim[1] < 0)
		dim[1] = 0;
	dim[2] = dim[0] / 2 + 540;
	if (dim[2] >= 1080)
		dim[2] = 1079;
}

/* CUORE RENDERING: Scrittura diretta in memoria (buffer) senza funzioni esterne */
void	draw_3d_projection(t_game *g, t_ray *r, int x)
{
	int		dim[3];
	double	tex_val[2];
	t_img	*t;
	int		var[2];
	int		*buffer;

	buffer = (int *)g->ghost_image.addr;
	t = get_texture(g, r);
	var[0] = get_tex_x(g, r, t);
	calc_wall(r, dim);
	tex_val[0] = 1.0 * t->height / dim[0];
	tex_val[1] = (dim[1] - 540 + dim[0] / 2) * tex_val[0];
	var[1] = -1;
	while (++var[1] < 1080)
	{
		if (var[1] < dim[1])
			buffer[var[1] * 1920 + x] = g->map.ceiling_color;
		else if (var[1] >= dim[1] && var[1] <= dim[2])
		{
			buffer[var[1] * 1920 + x] = get_pixel_color(t, var[0],
					(int)tex_val[1]);
			tex_val[1] += tex_val[0];
		}
		else
			buffer[var[1] * 1920 + x] = g->map.floor_color;
	}
}