/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* init_engine.c                                      :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/03/25 15:59:51 by vacuccu           #+#    #+#             */
/* Updated: 2026/04/14 13:10:00 by vacuccu          ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* QUA INIZIALIZZO LA FINESTRA CON I DATI PER LE DIMENSIONI E PER LE IMG */
static void	init_mlx_image(t_game *game)
{
	game->window = mlx_new_window(game->mlx, 1920, 1080, "CUB3D");
	if (!game->window)
		error_exit("Errore: Impossibile creare la finestra MLX", game);
	game->ghost_image.img = mlx_new_image(game->mlx, 1920, 1080);
	if (!game->ghost_image.img)
		error_exit("Errore: Impossibile creare l'immagine MLX", game);
	game->ghost_image.addr = mlx_get_data_addr(game->ghost_image.img,
			&game->ghost_image.bits_per_pixel,
			&game->ghost_image.line_length,
			&game->ghost_image.endian);
}

/* QUA SETTO I VALORI DI DEFAULT PER LE COORDINATE DEL PLAYER */
static void	set_player_vectors(t_game *game)
{
	game->player.dir.x = 0;
	game->player.dir.y = 0;
	game->player.plane.x = 0;
	game->player.plane.y = 0;
	if (game->player.spawn_dir == 'N')
	{
		game->player.dir.y = -1;
		game->player.plane.x = 0.66;
	}
	else if (game->player.spawn_dir == 'S')
	{
		game->player.dir.y = 1;
		game->player.plane.x = -0.66;
	}
	else if (game->player.spawn_dir == 'E')
	{
		game->player.dir.x = 1;
		game->player.plane.y = -0.66;
	}
	else if (game->player.spawn_dir == 'W')
	{
		game->player.dir.x = -1;
		game->player.plane.y = -0.66;
	}
}

static void	load_single_texture(t_game *game, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		error_exit("Errore: Impossibile caricare la texture XPM", game);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
}

static void	load_textures(t_game *game)
{
	load_single_texture(game, &game->textures.n_tex, game->textures.north);
	load_single_texture(game, &game->textures.s_tex, game->textures.south);
	load_single_texture(game, &game->textures.w_tex, game->textures.west);
	load_single_texture(game, &game->textures.e_tex, game->textures.east);
}

/* INIZIALIZZAZIONE VERA E PROPRIA DELLA FINESTRA */
void	init_engine(t_game *game)
{
	// 1. Inizializza la MLX
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("MLX init failed", game);
		
	// 2. Carica le 4 texture usando la funzione di supporto
	load_textures(game); 
	
	// 3. Crea la finestra e l'immagine usando la funzione di supporto
	init_mlx_image(game);
	
	// 4. Imposta la direzione in cui guarda il giocatore all'avvio
	set_player_vectors(game);

	// Eventuali Hooks (se li agganci altrove nel codice, lasciali lì, 
	// altrimenti scommentali e agganciali qui)
	// mlx_hook(game->window, 17, 0, close_game, game);
	// mlx_hook(game->window, 2, 1L<<0, handle_keypress, game);
}
