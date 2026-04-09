/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:07:17 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/30 11:23:40 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Controlla a fine lettura se manca qualche dato fondamentale */
static void	check_parsed_data(t_game *game)
{
	if (!game->textures.north || !game->textures.south
		|| !game->textures.west || !game->textures.east)
		error_exit("Missing textures", game);
	validate_map(game);
}

/* Gestisce solo le righe lette PRIMA che inizi la mappa */
static void	parse_header_line(t_game *game, char *line, char *trimmed,
		int *map_started)
{
	if (is_textures_line(trimmed))
		parse_textures(game, line);
	else if (is_color_line(trimmed))
		parse_color(game, line);
	else if (is_map_line(trimmed))
	{
		*map_started = 1;
		parse_map(game, line);
	}
	else
	{
		error_exit("Invalid line in header", game);
	}
}

/* Smista la riga corrente: la ignora se vuota, o la manda al parser corretto */
static void	process_line(t_game *game, char *line, int *map_started)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (is_empty_line(trimmed))
	{
		if (*map_started)
			error_exit("Empty line inside map", game);
		return ;
	}
	if (!*map_started)
		parse_header_line(game, line, trimmed, map_started);
	else
	{
		if (!is_map_line(trimmed))
			error_exit("Invalid map line", game);
		parse_map(game, line);
	}
}
/* Apre il file .cub e legge riga per riga */
void	parse_file(t_game *game, char *filename)
{
	int		fd;
	int		map_started;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file", game);
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		process_line(game, line, &map_started);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	check_parsed_data(game);
}
