/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:40:38 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/21 11:52:29 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_mlx_image(t_game *game)
{
	game->window = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (!game->window)
		error_exit("Errore: Impossibile creare la finestra MLX", game);
	game->ghost_image.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
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

void	init_engine(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("MLX init failed", game);
	load_textures(game);
	init_mlx_image(game);
	set_player_vectors(game);
	mlx_mouse_hide(game->mlx, game->window);
	mlx_hook(game->window, 6, (1L << 6), &handle_mouse_move, game);
}
