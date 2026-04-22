/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:42:53 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/22 10:04:31 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	close_game(t_game *game)
{
	if (game->textures.n_tex.img)
		mlx_destroy_image(game->mlx, game->textures.n_tex.img);
	if (game->textures.s_tex.img)
		mlx_destroy_image(game->mlx, game->textures.s_tex.img);
	if (game->textures.w_tex.img)
		mlx_destroy_image(game->mlx, game->textures.w_tex.img);
	if (game->textures.e_tex.img)
		mlx_destroy_image(game->mlx, game->textures.e_tex.img);
	if (game->textures.f_tex.img)
		mlx_destroy_image(game->mlx, game->textures.f_tex.img);
	if (game->textures.c_tex.img)
		mlx_destroy_image(game->mlx, game->textures.c_tex.img);
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
