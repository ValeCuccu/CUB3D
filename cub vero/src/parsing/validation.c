#include "../../inc/cub3d.h"

/* Controlla se un carattere è valido nella mappa */
static int is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

/* Riempie con spazi una riga fino alla larghezza massima */
static void pad_row(char **row, int width)
{
    int len = ft_strlen(*row);
    if (len >= width)
        return;

    char *new_row = malloc(sizeof(char) * (width + 1));
    if (!new_row)
        error_exit("Malloc failed in pad_row", NULL);

    ft_memcpy(new_row, *row, len);

    int i = len;
    while (i < width)
    {
        new_row[i] = ' ';
        i++;
    }
    new_row[width] = '\0';

    free(*row);
    *row = new_row;
}

/* Controlla che i bordi della mappa siano chiusi */
static void check_borders(t_game *game)
{
    int i = 0;
    int j = 0;

    // Prime e ultime righe
    j = 0;
    while (j < game->map.width)
    {
        if (game->map.grid[0][j] != '1' && game->map.grid[0][j] != ' ')
            error_exit("Map not closed at top border", game);
        if (game->map.grid[game->map.height - 1][j] != '1' &&
            game->map.grid[game->map.height - 1][j] != ' ')
            error_exit("Map not closed at bottom border", game);
        j++;
    }

    // Prime e ultime colonne
    i = 0;
    while (i < game->map.height)
    {
        if (game->map.grid[i][0] != '1' && game->map.grid[i][0] != ' ')
            error_exit("Map not closed at left border", game);
        if (game->map.grid[i][game->map.width - 1] != '1' &&
            game->map.grid[i][game->map.width - 1] != ' ')
            error_exit("Map not closed at right border", game);
        i++;
    }
}

/* Valida tutta la mappa */
void validate_map(t_game *game)
{
    int i = 0;
    int j;
    int player_count = 0;

    // Determina larghezza massima
    game->map.width = 0;
    while (i < game->map.height)
    {
        int len = ft_strlen(game->map.grid[i]);
        if (len > game->map.width)
            game->map.width = len;
        i++;
    }

    // Pad delle righe
    i = 0;
    while (i < game->map.height)
    {
        pad_row(&game->map.grid[i], game->map.width);
        i++;
    }

    // Controllo caratteri validi e posizione del player
    i = 0;
    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            char c = game->map.grid[i][j];
            if (!is_valid_map_char(c))
                error_exit("Invalid character in map", game);

            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                player_count++;
                game->player.pos.x = (double)j + 0.5;
                game->player.pos.y = (double)i + 0.5;
                game->player.spawn_dir = c;
            }
            j++;
        }
        i++;
    }

    if (player_count != 1)
        error_exit("Map must contain exactly one player", game);

    // Controllo spazi interni non permessi
    i = 1;
    while (i < game->map.height - 1)
    {
        j = 1;
        while (j < game->map.width - 1)
        {
            if (game->map.grid[i][j] == ' ')
                error_exit("Invalid space inside map", game);
            j++;
        }
        i++;
    }

    // Controllo bordi
    check_borders(game);
}