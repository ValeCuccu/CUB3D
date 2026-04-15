/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:43:56 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/15 14:55:59 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

/* Il cuore della renderizzazione della texture per quella specifica colonna verticale.
(Nota: L'array bounds contiene 3 dati: bounds[0] = altezza della riga,
bounds[1] = pixel di partenza in Y dello schermo, bounds[2] = pixel di fine in Y dello schermo.
Lo usiamo per non sforare i parametri della Norminette).
step = 1.0 * t->height / bounds[0];: Di quanto devo scendere sulla texture per ogni pixel dello schermo? Se il muro a schermo è alto 128 pixel, ma la texture è alta 64 pixel, step sarà 0.5. Significa che prenderò lo stesso pixel della texture due volte consecutive sullo schermo (scalando l'immagine verso l'alto).
t_pos = (bounds[1] - WIN_HEIGHT / 2 + bounds[0] / 2) * step;: Se mi trovo appiccicato al muro, il muro sarà più grande del mio schermo e quindi la sua cima finirà fuori (in numeri negativi). Questa formula calcola l'esatto offset da cui iniziare a leggere la texture saltando la parte che sta "fuori dallo schermo in alto".
Nel ciclo while: t_y = (int)t_pos; converte la nostra posizione decimale della texture nel pixel intero Y.
I due controlli if (t_y >= t->height) sono sicurezze per impedire glitch grafici dovuti all'arrotondamento dei double.
t_pos += step;: Ogni volta che scendiamo di un pixel sullo schermo, avanziamo di step pixel sull'immagine della texture. */
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

/* La funzione "padre" che calcola le dimensioni della colonna e chiama le altre.

bounds[0] = (int)(WIN_HEIGHT / ray->perp_wall_dist);: Calcola l'altezza del muro a schermo.
 Più sei distante (perp_wall_dist è grande), più la divisione dà un numero piccolo (muro lontano = basso).
  Più sei vicino, più dà un numero grande (muro vicino = altissimo). perp_wall_dist previene l'effetto distorsione fish-eye.
bounds[1] = -bounds[0] / 2 + WIN_HEIGHT / 2;: Trova la Y in cui iniziare a disegnare il muro, centrandolo rispetto allo schermo.
if (bounds[1] < 0) bounds[1] = 0;: Se la cima del muro è oltre il limite superiore dello schermo, blocca l'inizio del disegno a 0.
Uguale per la fine del muro bounds[2], bloccandola a WIN_HEIGHT - 1 per non farci crashare. */
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
