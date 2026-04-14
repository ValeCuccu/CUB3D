/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:02:33 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/13 17:59:48 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int  is_number(char *str)
{
    int i;
    int j;

    if (!str || str[0] == '\0')
        return (0);
    
    // Salta gli spazi iniziali
    i = 0;
    while (str[i] == ' ' || str[i] == '\t')
        i++;
        
    // Se la stringa era vuota o conteneva solo spazi
    if (str[i] == '\0')
        return (0);
        
    // Controlla che il resto siano numeri (o spazi finali)
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
        {
            // Se troviamo un carattere che non è un numero,
            // è valido SOLO se è uno spazio e tutti i caratteri 
            // successivi fino alla fine sono anch'essi spazi.
            j = i;
            while (str[j] == ' ' || str[j] == '\t')
                j++;
            if (str[j] == '\0')
                return (1); // Erano solo spazi finali, tutto ok
            return (0); // Abbiamo trovato qualcosa di strano (es. "12a3" o "12 3")
        }
        i++;
    }
    return (1);
}

static void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void    parse_color_value(char *str, t_color *color, t_game *game)
{
    char    **split;
    char    *clean_str; // Aggiungiamo una variabile per la stringa pulita
    int     i;

    // 1. Rimuoviamo il \n e gli spazi finali
    clean_str = ft_strtrim(str, " \n\t");
    if (!clean_str)
        error_exit("Malloc failed", game);

    // 2. Dividiamo la stringa pulita
    split = ft_split(clean_str, ',');
    
    // 3. Liberiamo la stringa pulita perché non ci serve più
    free(clean_str); 

    if (!split)
        error_exit("Malloc failed", game);
    
    i = 0;
    while (split[i])
        i++;
    
    if (i != 3)
    {
        free_split(split);
        error_exit("Invalid RGB format", game);
    }
    
    if (!is_number(split[0]) || !is_number(split[1]) || !is_number(split[2]))
    {
        free_split(split);
        error_exit("Invalid RGB value", game);
    }
    
    color->r = ft_atoi(split[0]);
    color->g = ft_atoi(split[1]);
    color->b = ft_atoi(split[2]);
    
    if (color->r < 0 || color->r > 255
        || color->g < 0 || color->g > 255
        || color->b < 0 || color->b > 255)
    {
        free_split(split);
        error_exit("RGB value out of range", game);
    }
    free_split(split);
}

void	parse_color(t_game *game, char *line)
{
	char	*trimmed;

	trimmed = skip_spaces(line);
	if (!ft_strncmp(trimmed, "F ", 2))
	{
		if (game->floor_set)
			error_exit("Duplicate floor color", game);
		parse_color_value(trimmed + 2, &game->floor, game);
		game->map.floor_color = rgb_to_int(game->floor);
		game->floor_set = 1;
	}
	else if (!ft_strncmp(trimmed, "C ", 2))
	{
		if (game->ceiling_set)
			error_exit("Duplicate ceiling color", game);
		parse_color_value(trimmed + 2, &game->ceiling, game);
		game->map.ceiling_color = rgb_to_int(game->ceiling);
		game->ceiling_set = 1;
	}
	else
	{
		error_exit("Invalid color identifier", game);
	}
}

