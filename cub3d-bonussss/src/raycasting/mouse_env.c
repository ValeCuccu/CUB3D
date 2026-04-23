/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_env_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:50:44 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/23 10:49:04 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	handle_mouse_move(int x, int y, t_game *game)
{
	int	dx;

	(void)y;
	dx = x - (WIN_WIDTH / 2);
	if (dx != 0)
	{
		rotate_player(game, dx * MOUSE_SENSITIVITY);
		mlx_mouse_move(game->mlx, game->window, WIN_WIDTH / 2,
			WIN_HEIGHT / 2);
	}
	return (0);
}
