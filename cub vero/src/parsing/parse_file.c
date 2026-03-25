/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:07:17 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/25 13:11:24 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	parse_file(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	int		map_started;
	char	*trimmed;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file", game);
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		trimmed = skip_spaces(line);
		if (is_empty_line(trimmed))
		{
			if (map_started)
				error_exit("Empty line inside map", game);
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!map_started)
		{
			if (is_textures_line(trimmed))
				parse_textures(game, line);
			else if (is_color_line(trimmed))
				parse_color(game, line);
			else if (is_map_line(trimmed))
			{
				map_started = 1;
				parse_map(game, line);
			}
			else
				error_exit("Invalid line in header", game);
		}
		else
		{
			if (!is_map_line(trimmed))
				error_exit("Invalid map line", game);
			parse_map(game, line);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!game->textures.no || !game->textures.so
		|| !game->textures.we || !game->textures.ea)
		error_exit("Missing textures(s)", game);
	validate_map(game);
}
