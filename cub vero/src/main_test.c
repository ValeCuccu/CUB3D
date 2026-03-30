/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:24:06 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/25 13:27:58 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/cub3d.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
    {
        printf("Usage: %s <map_file.cub>\n", argv[0]);
        return 1;
    }

    // Inizializza tutta la struct a zero
    ft_bzero(&game, sizeof(t_game));

    // Parsing del file
    parse_file(&game, argv[1]);

    // Se arriviamo qui, il parsing è OK
    printf("Parsing completato con successo!\n\n");

    printf("Map (%d righe):\n", game.map.height);
    for (int i = 0; i < game.map.height; i++)
        printf("%s\n", game.map.grid[i]);

    printf("\nPlayer: (%.1f, %.1f), spawn_dir: %c\n",
           game.player.pos.x, game.player.pos.y, game.player.spawn_dir);

    // Libera la memoria usata
    free_map(&game);
    free_textures(&game);

    return 0;
}
