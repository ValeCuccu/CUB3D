/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 12:53:42 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/24 11:49:39 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#define TILE_SIZE 64

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 1024 || y < 0 || y >= 512)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// --- FUNZIONI PER IL 2D (MINIMAPPA) ---

// Disegna un singolo quadrato pieno (un blocco della mappa)
void draw_square(t_game *game, int x, int y, int size, int color)
{
    int i;
    int j;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            // Lasciamo 1 pixel di bordo nero per vedere la griglia, come fa 3DSage [00:05:01]
            if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
                my_mlx_pixel_put(&game->ghost_image, x + j, y + i, 0x000000); // Bordo nero
            else
                my_mlx_pixel_put(&game->ghost_image, x + j, y + i, color);    // Interno
            j++;
        }
        i++;
    }
}

// Legge la matrice della mappa e la disegna a blocchi
void render_minimap(t_game *game)
{
    int i;
    int j;
    int color;

    i = 0;
    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            if (game->map.grid[i][j] == '1')
                color = 0xFFFFFF; // Muro: Bianco
            else
                color = 0x555555; // Spazio vuoto: Grigio scuro

            // Calcoliamo la posizione in pixel moltiplicando per TILE_SIZE
            draw_square(game, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, color);
            j++;
        }
        i++;
    }
}

// Disegna il giocatore come un quadratino giallo
void render_player(t_game *game)
{
    // Calcoliamo la posizione esatta in pixel
    int px = (int)(game->player.pos.x * TILE_SIZE);
    int py = (int)(game->player.pos.y * TILE_SIZE);
    
    // Lo facciamo grande 6 pixel (centrato)
    int player_size = 10;
    draw_square(game, px - (player_size/2), py - (player_size/2), player_size, 0xFFFF00); // Giallo
    
    // Bonus: Disegniamo anche una piccola linea per mostrare dove sta guardando!
    int end_x = px + (int)(game->player.dir.x * 20); // 20 pixel di lunghezza
    int end_y = py + (int)(game->player.dir.y * 20);
    
    // Un modo super banale per fare una linea (senza usare algoritmi complessi come Bresenham)
    // è campionare dei punti lungo il vettore.
    for (double i = 0; i <= 1.0; i += 0.05) {
        int lx = px + (int)((end_x - px) * i);
        int ly = py + (int)((end_y - py) * i);
        my_mlx_pixel_put(&game->ghost_image, lx, ly, 0xFF0000); // Linea Rossa
    }
}

// --- RENDER FRAME ---
int render_frame(t_game *game)
{
    // 1. Sfondo tutto nero prima di disegnare
    for (int y = 0; y < 512; y++)
        for (int x = 0; x < 1024; x++)
            my_mlx_pixel_put(&game->ghost_image, x, y, 0x000000);

    // 2. Disegniamo la mappa dall'alto
    render_minimap(game);
    
    // 3. Disegniamo il giocatore e la direzione in cui guarda
    render_player(game);

    // 4. Spingiamo a schermo
    mlx_put_image_to_window(game->mlx, game->window, game->ghost_image.img, 0, 0);
    return (0);
}