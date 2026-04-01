/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:24:06 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/01 13:12:22 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
    //printf("Parsing completato con successo!\n\n");
	init_engine(&game);
	// --- AGGIUNGI SOLO QUESTE RIGHE ---
    
    // Gestisce il click sulla X della finestra
    mlx_hook(game.window, 17, 0, close_game, &game);
    
    // Gestisce la pressione dei tasti (ESC)
    mlx_hook(game.window, 2, 1L<<0, handle_keypress, &game);
	
	/* qui chiamo il motore vero e proprio che renderizza tutto ad ogni frame */
	mlx_loop_hook(game.mlx, render_frame, &game);

    printf("Finestra creata. Premi ESC o la X per chiudere.\n");
    
    // Avvia il loop (senza questo la finestra non risponde)
    mlx_loop(game.mlx);

    return 0;
}
