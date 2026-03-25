/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:15:42 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/25 13:18:06 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
 * parse_textures:
 *  - legge una riga di textures (NO, SO, WE, EA)
 *  - salva il percorso nella struct t_game
 *  - gestisce duplicati
 *  - rimuove spazi iniziali
 */
void	parse_textures(t_game *game, char *line)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (!ft_strncmp(trimmed, "NO ", 3))
	{
		if (game->textures.no)
			error_exit("Duplicate NO textures", game);
		game->textures.no = ft_strdup(skip_spaces(trimmed + 3));
		if (!game->textures.no || game->textures.no[0] == '\0')
			error_exit("Invalid NO textures path", game);
	}
	else if (!ft_strncmp(trimmed, "SO ", 3))
	{
		if (game->textures.so)
			error_exit("Duplicate SO textures", game);
		game->textures.so = ft_strdup(skip_spaces(trimmed + 3));
		if (!game->textures.so || game->textures.so[0] == '\0')
			error_exit("Invalid SO textures path", game);
	}
	else if (!ft_strncmp(trimmed, "WE ", 3))
	{
		if (game->textures.we)
			error_exit("Duplicate WE textures", game);
		game->textures.we = ft_strdup(skip_spaces(trimmed + 3));
		if (!game->textures.we || game->textures.we[0] == '\0')
			error_exit("Invalid WE textures path", game);
	}
	else if (!ft_strncmp(trimmed, "EA ", 3))
	{
		if (game->textures.ea)
			error_exit("Duplicate EA textures", game);
		game->textures.ea = ft_strdup(skip_spaces(trimmed + 3));
		if (!game->textures.ea || game->textures.ea[0] == '\0')
			error_exit("Invalid EA textures path", game);
	}
	else
	{
		error_exit("Invalid textures identifier", game);
	}
}
