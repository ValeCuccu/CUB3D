/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:15:42 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/25 15:18:06 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	save_textures(t_game *game, char **texture, char *path)
{
	if (*texture)
		error_exit("Duplicate texture found", game);
	*texture = ft_strdup (skip_spaces(path));
	if (!*texture || (*texture)[0] == '\0')
		error_exit("Invalid texture path", game);
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