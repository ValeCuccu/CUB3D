/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:27:18 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/25 15:41:15 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Controlla se un carattere è valido nella mappa */
int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

/* Riempie con spazi una riga fino alla larghezza massima */
void	pad_row(char **row, int width)
{
	int		len;
	int		i;
	char	*new_row;

	len = ft_strlen(*row);
	if (len >= width)
		return ;
	new_row = malloc(sizeof(char) * (width + 1));
	if (!new_row)
		error_exit("Malloc failed in pad_row", NULL);
	ft_memcpy(new_row, *row, len);
	i = len;
	while (i < width)
	{
		new_row[i] = ' ';
		i++;
	}
	new_row[width] = '\0';
	free(*row);
	*row = new_row;
}

/* Controlla che i bordi della mappa siano chiusi */
void	check_borders(t_game *game)
{
	int	i;
	int	j;

	// Prime e ultime righe
	j = 0;
	while (j < game->map.width)
	{
		if (game->map.grid[0][j] != '1' && game->map.grid[0][j] != ' ')
			error_exit("Map not closed at top border", game);
		if (game->map.grid[game->map.height - 1][j] != '1' &&
			game->map.grid[game->map.height - 1][j] != ' ')
			error_exit("Map not closed at bottom border", game);
		j++;
	}
    // Prime e ultime colonne
	i = 0;
	while (i < game->map.height)
	{
		if (game->map.grid[i][0] != '1' && game->map.grid[i][0] != ' ')
			error_exit("Map not closed at left border", game);
		if (game->map.grid[i][game->map.width - 1] != '1' &&
			game->map.grid[i][game->map.width - 1] != ' ')
			error_exit("Map not closed at right border", game);
		i++;
	}
}
