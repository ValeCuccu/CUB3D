/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:20:28 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/09 13:51:25 by vacuccu          ###   ########.fr       */
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
		free_map(game);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

/* Libera tutte le strutture allocate di t_game */
void	free_map(t_game *game)
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
}

void	free_textures(t_game *game)
{
	if (game->textures.north)
		free(game->textures.north);
	if (game->textures.south)
		free(game->textures.south);
	if (game->textures.west)
		free(game->textures.west);
	if (game->textures.east)
		free(game->textures.east);
	game->textures.north = NULL;
	game->textures.south = NULL;
	game->textures.west = NULL;
	game->textures.east = NULL;
	/* In futuro, se ci fossero colori dinamici allocati, li si libererebbe qui */
	// free(game->floor);
	// free(game->ceiling);
}

int	rgb_to_int(t_color c)
{
	return (c.r << 16 | c.g << 8 | c.b);
}
