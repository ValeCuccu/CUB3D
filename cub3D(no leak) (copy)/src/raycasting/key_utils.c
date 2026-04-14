/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:55:21 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/14 13:53:12 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	handle_keypress(int key, t_game *game)
{
	if (key == ESC)
		close_game(game);
	else if (key == W)
		apply_movement(game, game->player.dir.x, game->player.dir.y);
	else if (key == S)
		apply_movement(game, -game->player.dir.x, -game->player.dir.y);
	else if (key == A)
		apply_movement(game, game->player.dir.y, -game->player.dir.x);
	else if (key == D)
		apply_movement(game, -game->player.dir.y, game->player.dir.x);
	else if (key == LEFT) // Freccia Sinistra (Linux)
		rotate_player(game, -1);
	else if (key == RIGHT) // Freccia Destra (Linux)
		rotate_player(game, 1);
	return (0);
}

void	apply_movement(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	// Calcoliamo dove vorrebbe andare il player
	new_x = game->player.pos.x + move_x * MOVE_SPEED;
	new_y = game->player.pos.y + move_y * MOVE_SPEED;
	// 1. Controllo collisione asse X
	if (game->map.grid[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	// 2. Controllo collisione asse Y
	if (game->map.grid[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
}

void rotate_player(t_game *game, double rot)
{
    double old_dir_x;
    double old_plane_x;

    // 1. Salva la vecchia X della direzione
    old_dir_x = game->player.dir.x;
    // 2. Ruota la direzione usando VECCHIA X per calcolare la Y
    game->player.dir.x = game->player.dir.x * cos(rot) - game->player.dir.y * sin(rot);
    game->player.dir.y = old_dir_x * sin(rot) + game->player.dir.y * cos(rot);

    // 3. Ripeti la stessa identica cosa per il piano della telecamera (FOV)
    old_plane_x = game->player.plane.x;
    game->player.plane.x = game->player.plane.x * cos(rot) - game->player.plane.y * sin(rot);
    game->player.plane.y = old_plane_x * sin(rot) + game->player.plane.y * cos(rot);
}
