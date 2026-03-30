/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 17:59:46 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/24 11:47:50 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	close_game(t_game *game)
{
	// da aggiungere successivamente una free_game() personalizzata
	if (game->ghost_image.img)
		mlx_destroy_image(game->mlx, game->ghost_image.img);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		free(game->mlx);
	printf("Uscita da CUB3D con Successo!\n");
	exit(0);
	return (0);
}
