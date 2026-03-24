/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 18:07:32 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/24 13:05:49 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int main(int argc, char **argv)
{
    t_game game;

    (void)argv;
    if (argc != 2)
    {
        printf("Error\nUso: ./cub3D <percorso_mappa.cub>\n");
        return (1);
    }

    ft_bzero(&game, sizeof(t_game));

    // --- LA TUA MAPPA FINTA ---
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
    
    // Posizione iniziale e direzione del player
    game.player.pos.x = 2;
    game.player.pos.y = 0.5;
    game.player.spawn_dir = 'W';

    // 1. Inizializza la finestra e l'immagine ghost
    init_engine(&game);

    // 2. DISEGNA LA SCHERMATA INIZIALE!
    render_frame(&game);

    // 3. Attiva i controlli della tastiera
    mlx_hook(game.window, 2, 1L<<0, key_press, &game);
    mlx_hook(game.window, 17, 0, close_game, &game);
    
    // 4. Mette in pausa il programma e aspetta che tu prema i tasti
    mlx_loop(game.mlx);

    return (0);
}