/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:40:52 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/30 17:30:00 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Controlla se un carattere rappresenta un player */
static int is_player(char c)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return 1;
    return 0;
}

/* Controlla che ogni '0' o player non abbia attorno spazi o caratteri invalidi */
bool check_map_8neighbors(t_game *game)
{
    int y = 0;
    while (y < game->map.height)
    {
        int x = 0;
        while (x < (int)ft_strlen(game->map.grid[y]))
        {
            char c = game->map.grid[y][x];
            if (c == '0' || is_player(c))
            {
                int dy = -1;
                while (dy <= 1)
                {
                    int dx = -1;
                    while (dx <= 1)
                    {
                        if (dy != 0 || dx != 0) // escludi la cella centrale
                        {
                            int ny = y + dy;
                            int nx = x + dx;
                            if (ny < 0 || ny >= game->map.height)
                                return false;
                            if (nx < 0 || nx >= (int)ft_strlen(game->map.grid[ny]))
                                return false;
                            char nc = game->map.grid[ny][nx];
                            if (nc != '0' && nc != '1' && !is_player(nc))
                                return false;
                        }
                        dx++;
                    }
                    dy++;
                }
            }
            x++;
        }
        y++;
    }
    return true;
}

/* Valida la mappa completa */
void validate_map(t_game *game)
{
    int y = 0;
    int player_count = 0;

    while (y < game->map.height)
    {
        int x = 0;
        while (x < (int)ft_strlen(game->map.grid[y]))
        {
            char c = game->map.grid[y][x];
            if (c != '0' && c != '1' && !is_player(c))
                error_exit("Invalid map character", game);
            if (is_player(c))
            {
                player_count++;
                game->player.pos.x = (double)x + 0.5;
                game->player.pos.y = (double)y + 0.5;
                game->player.spawn_dir = c;
            }
            x++;
        }
        y++;
    }

    if (player_count != 1)
        error_exit("Map must contain exactly one player", game);

    if (!check_map_8neighbors(game))
        error_exit("Map is not closed: '0' or player touches invalid cell", game);
}