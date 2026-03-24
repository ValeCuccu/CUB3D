/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 18:07:32 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/23 18:57:21 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int main(int argc, char **argv)
{
    t_game game;
    (void)argv;

    printf("[1] Avvio programma...\n");
    if (argc != 2)
    {
        printf("Error\nUso: ./cub3D <percorso_mappa.cub>\n");
        return (1);
    }

    // Puliamo la struct
    ft_bzero(&game, sizeof(t_game));

    printf("[2] Caricamento mappa 2D finta...\n");
    // La mappa 8x8 per testare la visuale dall'alto
    static char *fake_map[] = {
        "11111111",
        "10000001",
        "10010001",
        "10000001",
        "10000001",
        "10000001",
        "10000001",
        "11111111"
    };
    game.map.grid = (char **)fake_map;
    game.map.width = 8;
    game.map.height = 8;
    
    // Giocatore al centro della mappa 2D
    game.player.pos.x = 4.5;
    game.player.pos.y = 4.5;
    game.player.spawn_dir = 'N';

    printf("[3] Inizializzazione MLX...\n");
    init_engine(&game);

    printf("[4] Disegno il mondo 2D visto dall'alto...\n");
    render_frame(&game);

    printf("[5] Avvio il loop degli eventi grafici...\n");
    mlx_hook(game.window, 2, 1L<<0, key_press, &game);
    mlx_hook(game.window, 17, 0, close_game, &game);
    mlx_loop(game.mlx);

    return (0);
}