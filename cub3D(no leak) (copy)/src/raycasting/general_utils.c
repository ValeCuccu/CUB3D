/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:42:53 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/09 19:35:37 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	close_game(t_game *game)
{
	free_textures(game);
	free_map(game);
	if (game->ghost_image.img)
		mlx_destroy_image(game->mlx, game->ghost_image.img);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	printf("Chiusura pulita eseguita\n");
	exit(0);
	return (0);
}
