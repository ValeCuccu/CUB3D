/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:59:51 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/02 15:23:32 by vacuccu          ###   ########.fr       */
/*                                                                            */
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

/* INIZIALIZZAZIONE VERA E PROPRIA DELLA FINESTRA USANDO LE FUNZIONI SOPRASTANTI PER INCORPORARE I VALORI NECESSARI */
void	init_engine(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("Error: failed inizialization for MLX\n", game);
	init_mlx_image(game);
	set_player_vectors(game);
}
