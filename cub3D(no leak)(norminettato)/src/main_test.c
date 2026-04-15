/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:24:06 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/15 12:54:17 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	if (!check_extension(argv[1]))
	{
		printf("Error\nInvalid file extension\n");
		return (1);
	}
	ft_bzero(&game, sizeof(t_game));
	parse_file(&game, argv[1]);
	init_engine(&game);
	mlx_hook(game.window, 17, 0, close_game, &game);
	mlx_hook(game.window, 2, 1L << 0, key_press, &game);
	mlx_hook(game.window, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	printf("Motore avviato. Usa WASD per muoverti e le Frecce per girare.\n");
	mlx_loop(game.mlx);
	return (0);
}
