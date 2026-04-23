/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:57:27 by anpastac          #+#    #+#             */
/*   Updated: 2026/04/23 10:48:04 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static void	check_file_exists(char *path, t_game *game)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Texture file not found", game);
	close(fd);
}

static void	save_textures(t_game *game, char **texture, char *path)
{
	char	*clean_path;

	if (*texture)
		error_exit("Duplicate texture found", game);
	clean_path = ft_strtrim(skip_spaces(path), " \n\t");
	if (!clean_path || clean_path[0] == '\0')
	{
		if (clean_path)
			free(clean_path);
		error_exit("Invalid texture path", game);
	}
	*texture = clean_path;
	check_file_exists(clean_path, game);
}

void	parse_textures(t_game *game, char *line)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (!ft_strncmp(trimmed, "NO ", 3))
		save_textures(game, &game->textures.north, trimmed + 3);
	else if (!ft_strncmp(trimmed, "SO ", 3))
		save_textures(game, &game->textures.south, trimmed + 3);
	else if (!ft_strncmp(trimmed, "WE ", 3))
		save_textures(game, &game->textures.west, trimmed + 3);
	else if (!ft_strncmp(trimmed, "EA ", 3))
		save_textures(game, &game->textures.east, trimmed + 3);
	else
		error_exit("Invalid textures detected", game);
}

int	rgb_to_int(t_color c)
{
	return (c.r << 16 | c.g << 8 | c.b);
}
