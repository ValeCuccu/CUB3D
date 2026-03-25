/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:20:28 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/25 13:20:29 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Rimuove gli spazi iniziali e tab da una stringa */
char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

/* Stampa un messaggio di errore, libera la memoria e termina il programma */
void	error_exit(char *msg, t_game *game)
{
	if (game)
		free_game(game);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

/* Libera tutte le strutture allocate di t_game */
void	free_game(t_game *game)
{
	int	i;

	if (game->map.grid)
	{
		i = 0;
		while (game->map.grid[i])
		{
			free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
		game->map.grid = NULL;
		game->map.height = 0;
		game->map.width = 0;
	}
	if (game->textures.no)
		free(game->textures.no);
	if (game->textures.so)
		free(game->textures.so);
	if (game->textures.we)
		free(game->textures.we);
	if (game->textures.ea)
		free(game->textures.ea);
	game->textures.no = NULL;
	game->textures.so = NULL;
	game->textures.we = NULL;
	game->textures.ea = NULL;
	/* In futuro, se ci fossero colori dinamici allocati, li si libererebbe qui */
	// free(game->floor);
	// free(game->ceiling);
}
