/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:57:27 by anpastac          #+#    #+#             */
/*   Updated: 2026/04/14 11:32:05 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Controlla a fine lettura se manca qualche dato fondamentale */
static void	check_parsed_data(t_game *game)
{
	if (!game->textures.north || !game->textures.south
		|| !game->textures.west || !game->textures.east)
		error_exit("Missing textures", game);
	if (!game->floor_set || !game->ceiling_set)
		error_exit("Missing floor or ceiling color", game);
	validate_map(game);
}

/* Gestisce solo le righe lette PRIMA che inizi la mappa */
static void	parse_header_line(t_game *game, char *line, char *trimmed,
		int *map_status)
{
	if (is_textures_line(trimmed))
		parse_textures(game, line);
	else if (is_color_line(trimmed))
		parse_color(game, line);
	else if (is_map_line(trimmed))
	{
		*map_status = 1;
		parse_map(game, line);
	}
	else
		error_exit("Invalid line in header", game);
}

/* Smista la riga corrente: la ignora se vuota, o manda al parser corretto */
static void	process_line(t_game *game, char *line, int *map_status)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (is_empty_line(trimmed))
	{
		if (*map_status == 1)
			*map_status = 2;
		return ;
	}
	if (*map_status == 0)
		parse_header_line(game, line, trimmed, map_status);
	else if (*map_status == 1)
	{
		if (!is_map_line(trimmed))
			error_exit("Invalid map line", game);
		parse_map(game, line);
	}
	else if (*map_status == 2)
		error_exit("Empty line inside map or content after map", game);
}

/* Apre il file .cub e legge riga per riga */
void	parse_file(t_game *game, char *filename)
{
	int	map_status;

	game->fd = open(filename, O_RDONLY);
	if (game->fd < 0)
		error_exit("Cannot open file", game);
	map_status = 0;
	game->current_line = get_next_line(game->fd);
	while (game->current_line)
	{
		process_line(game, game->current_line, &map_status);
		free(game->current_line);
		game->current_line = get_next_line(game->fd);
	}
	close(game->fd);
	game->fd = -1;
	check_parsed_data(game);
}
