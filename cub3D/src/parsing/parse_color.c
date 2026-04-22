#include "../../inc/cub3d.h"

/* Estrae il percorso .xpm e lo salva nella struct al posto del colore */
static void save_fc_path(t_game *game, char **tex_path, char *line, int *set)
{
    char    *clean_path;

    if (*tex_path || *set)
        error_exit("Duplicate floor or ceiling texture found", game);
    
    clean_path = ft_strtrim(skip_spaces(line), " \n\t");
    if (!clean_path || clean_path[0] == '\0')
    {
        if (clean_path)
            free(clean_path);
        error_exit("Invalid floor/ceiling texture path", game);
    }
    
    *tex_path = clean_path;
    *set = 1;
}

/* La funzione si chiama ancora parse_color per non rompere il resto del codice, 
   ma ora gestisce i percorsi delle texture! */
void    parse_color(t_game *game, char *line)
{
    char    *trimmed;

    trimmed = skip_spaces(line);
    if (!ft_strncmp(trimmed, "F ", 2))
        save_fc_path(game, &game->textures.floor, trimmed + 2, &game->floor_set);
    else if (!ft_strncmp(trimmed, "C ", 2))
        save_fc_path(game, &game->textures.ceiling, trimmed + 2, &game->ceiling_set);
    else
        error_exit("Invalid identifier", game);
}
