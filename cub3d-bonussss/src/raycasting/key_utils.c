/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:55:21 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/24 16:24:40 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	key_press(int key, t_game *game)
{
	if (key == ESC)
		close_game(game);
	if (key >= 0 && key < 65365)
		game->keys[key] = 1;
	if (key == TAB)
		game->mouse_lock = !game->mouse_lock;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key >= 0 && key < 65365)
		game->keys[key] = 0;
	return (0);
}

void	apply_movement(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + move_x * MOVE_SPEED;
	new_y = game->player.pos.y + move_y * MOVE_SPEED;
	if (game->map.grid[(int)game->player.pos.y][(int)new_x] != '1')
		game->player.pos.x = new_x;
	if (game->map.grid[(int)new_y][(int)game->player.pos.x] != '1')
		game->player.pos.y = new_y;
}

void	rotate_player(t_game *game, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(rot)
		- game->player.dir.y * sin(rot);
	game->player.dir.y = old_dir_x * sin(rot) + game->player.dir.y * cos(rot);
	old_plane_x = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(rot)
		- game->player.plane.y * sin(rot);
	game->player.plane.y = old_plane_x * sin(rot)
		+ game->player.plane.y * cos(rot);
}

void	update_player_state(t_game *game)
{
	if (game->keys[W])
		apply_movement(game, game->player.dir.x, game->player.dir.y);
	if (game->keys[S])
		apply_movement(game, -game->player.dir.x, -game->player.dir.y);
	if (game->keys[A])
		apply_movement(game, game->player.dir.y, -game->player.dir.x);
	if (game->keys[D])
		apply_movement(game, -game->player.dir.y, game->player.dir.x);
	if (game->keys[LEFT])
		rotate_player(game, -ROT_SPEED);
	if (game->keys[RIGHT])
		rotate_player(game, ROT_SPEED);
}
