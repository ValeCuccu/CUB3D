/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 11:44:57 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/24 12:07:01 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	move_forward_back(int keycode, t_game *game)
{
	t_player	*p;
	double		nx;
	double		ny;

	p = &game->player;
	if (keycode == 119)
	{
		nx = p->pos.x + p->dir.x * MOVE_SPEED;
		ny = p->pos.y + p->dir.y * MOVE_SPEED;
	}
	else
	{
		nx = p->pos.x - p->dir.x * MOVE_SPEED;
		ny = p->pos.y - p->dir.y * MOVE_SPEED;
	}
	if (game->map.grid[(int)p->pos.y][(int)nx] != '1')
		p->pos.x = nx;
	if (game->map.grid[(int)ny][(int)p->pos.x] != '1')
		p->pos.y = ny;
}

static void	move_left_right(int keycode, t_game *game)
{
	t_player	*p;
	double		nx;
	double		ny;

	p = &game->player;
	if (keycode == 100)
	{
		nx = p->pos.x - p->dir.y * MOVE_SPEED;
		ny = p->pos.y + p->dir.x * MOVE_SPEED;
	}
	else
	{
		nx = p->pos.x + p->dir.y * MOVE_SPEED;
		ny = p->pos.y - p->dir.x * MOVE_SPEED;
	}
	if (game->map.grid[(int)p->pos.y][(int)nx] != '1')
		p->pos.x = nx;
	if (game->map.grid[(int)ny][(int)p->pos.x] != '1')
		p->pos.y = ny;
}

static void	rotate_camera(int keycode, t_game *game)
{
	t_player	*p;
	double		old_dir;
	double		old_plane;
	double		rot;

	p = &game->player;
	rot = ROT_SPEED;
	if (keycode == 65361)
		rot = -ROT_SPEED;
	old_dir = p->dir.x;
	p->dir.x = p->dir.x * cos(rot) - p->dir.y * sin(rot);
	p->dir.y = old_dir * sin(rot) + p->dir.y * cos(rot);
	old_plane = p->plane.x;
	p->plane.x = p->plane.x * cos(rot) - p->plane.y * sin(rot);
	p->plane.y = old_plane * sin(rot) + p->plane.y * cos(rot);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		close_game(game);
	else if (keycode == 119 || keycode == 115)
		move_forward_back(keycode, game);
	else if (keycode == 97 || keycode == 100)
		move_left_right(keycode, game);
	else if (keycode == 65361 || keycode == 65363)
		rotate_camera(keycode, game);
	render_frame(game);
	return (0);
}