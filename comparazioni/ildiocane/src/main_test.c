/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:24:06 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/01 17:13:42 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int main(int argc, char **argv)
{
    t_game game;

    // 1. Controllo Argomenti
    if (argc != 2)
    {
        printf("Usage: %s <map_file.cub>\n", argv[0]);
        return (1);
    }

    // 2. Reset della struct (evita "garbage values")
    ft_bzero(&game, sizeof(t_game));

    // 3. PARSING (Il lavoro di Antonio)
    // Qui il programma legge il file, riempie game.map.grid, 
    // salva i colori e la posizione iniziale del player.
    parse_file(&game, argv[1]);

    // 4. INIZIALIZZAZIONE MOTORE
    // Ora che abbiamo i dati, creiamo la finestra e l'immagine.
    // Questa funzione userà game.player.spawn_dir per settare i vettori.
    init_engine(&game);

    // 5. HOOKS (Gli "orecchi" del programma)
    // Gestione chiusura con la X
    mlx_hook(game.window, 17, 0, close_game, &game);
    
    // Gestione tastiera (WASD + Frecce)
    mlx_hook(game.window, 2, 1L<<0, handle_keypress, &game);

    // 6. LOOP HOOK (Il "cuore" pulsante)
    // Chiama render_frame costantemente per ridisegnare la scena.
    mlx_loop_hook(game.mlx, render_frame, &game);

    // 7. START
    printf("Motore avviato. Usa WASD per muoverti e le Frecce per girare.\n");
    mlx_loop(game.mlx);

    return (0);
}
