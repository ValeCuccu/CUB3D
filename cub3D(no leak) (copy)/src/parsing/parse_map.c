/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:11:58 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/13 18:18:20 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	**resize_map(char **old, int new_size)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (new_size + 1));
	if (!new)
		error_exit("Malloc failed", NULL);

	i = 0;
	while (old && old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i] = NULL;
	free(old);
	return (new);
}

static void	add_map_line(t_game *game, char *line)
{
	char	**new_grid;

	if (!game->map.grid)
	{
		game->map.grid = malloc(sizeof(char *) * 2);
		if (!game->map.grid)
			error_exit("Malloc failed", game);
		game->map.grid[0] = ft_strdup(line);
		game->map.grid[1] = NULL;
		game->map.height = 1;
		return ;
	}
	new_grid = resize_map(game->map.grid, game->map.height + 1);
	new_grid[game->map.height] = ft_strdup(line);
	new_grid[game->map.height + 1] = NULL;
	game->map.grid = new_grid;
	game->map.height++;
}

void    parse_map(t_game *game, char *line)
{
    char    *clean;

    // Togliamo solo l'a capo finale, mantenendo tutti gli spazi!
    clean = ft_strtrim(line, "\n");
    if (!clean)
        error_exit("Malloc failed", game);

    // Visto che controlliamo già in process_line se la riga è vuota,
    // qui dobbiamo solo aggiungerla alla griglia.
    add_map_line(game, clean);
    
    // Ora clean punta sempre all'inizio del blocco allocato, 
    // quindi la free è sicura!
    free(clean); 
}
