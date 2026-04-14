/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:20:28 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/13 17:23:51 by anpastac         ###   ########.fr       */
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

void    cleanup_game(t_game *game)
{
    char *temp_line;

    if (!game)
        return;
    
    // 1. Libera la riga corrente se si è interrotto a metà
    if (game->current_line)
    {
        free(game->current_line);
        game->current_line = NULL;
    }
    
    // 2. Svuota il buffer statico di get_next_line leggendo fino alla fine
    // e chiude il file descriptor in modo sicuro
    if (game->fd > 0)
    {
        temp_line = get_next_line(game->fd);
        while (temp_line)
        {
            free(temp_line);
            temp_line = get_next_line(game->fd);
        }
        close(game->fd);
        game->fd = -1;
    }

    free_textures(game);
    free_map(game);
}

/* Stampa un messaggio di errore, libera la memoria e termina il programma */
void	error_exit(char *msg, t_game *game)
{
	cleanup_game(game);
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
}
