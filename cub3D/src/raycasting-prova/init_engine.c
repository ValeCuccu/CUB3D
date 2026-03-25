/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 12:53:00 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/25 10:34:34 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* in questo file inizializzo la finestra con mlx i vettori del giocatore e la direzione di spawn */

static void	init_mlx_image(t_game *game)
{
	game->window = mlx_new_window(game->mlx, 1024, 512, "CUB3D");
	if (!game->window)
		error_exit("Errore: Impossibile creare la finestra MLX", game);
	game->ghost_image.img = mlx_new_image(game->mlx, 1024, 512);
	if (!game->ghost_image.img)
		error_exit("Errore: Impossibile creare l'immagine MLX", game);
	game->ghost_image.addr = mlx_get_data_addr(game->ghost_image.img,
			&game->ghost_image.bits_per_pixel,
			&game->ghost_image.line_length,
			&game->ghost_image.endian);
}

static void	set_player_vectors(t_game *game)
{
	game->player.dir.x = 0;
	game->player.dir.y = 0;
	game->player.plane.x = 0;
	game->player.plane.y = 0;
	if (game->player.spawn_dir == 'N')
	{
		game->player.dir.y = -1;
		game->player.plane.x = 0.70;
	}
	else if (game->player.spawn_dir == 'S')
	{
		game->player.dir.y = 1;
		game->player.plane.x = -0.70;
	}
	else if (game->player.spawn_dir == 'E')
	{
		game->player.dir.y = 1;
		game->player.plane.x = -0.70;
	}
	else if (game->player.spawn_dir == 'W')
	{
		game->player.dir.y = -1;
		game->player.plane.x = -0.70;
	}
}

void	init_engine(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("Errore: Inizializzazione MLX fallita", game);
	init_mlx_image(game);
	set_player_vectors(game);
}