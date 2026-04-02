/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:45:02 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/02 17:31:18 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.01
# define TILE_SIZE 64
# define ESC 65307
# define W 119
# define S 115
# define A 97
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define MMAP_SCALE 10
# define MMAP_OFFSET 20

/* DIPENDENZE */
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
/*# include "minilibx-linux/mlx.h"*/

/* RAGGI */
/* questa struct contiene tutte le variabilli che servono al dda per calcolare traiettoria e collisione */
typedef struct s_ray
{
	double	ray_dir_x; // Direzione X specifica di questo raggio (somma di dir_x e plane_x * camera_x)
	double	ray_dir_y; // Direzione Y specifica di questo raggio (somma di dir_y e plane_y * camera_x)
	int		map_x;     // Coordinata X (colonna) della casella della griglia in cui si trova il raggio
	int		map_y;     // Coordinata Y (riga) della casella della griglia in cui si trova il raggio
	double	delta_x;   // Distanza che il raggio deve percorrere per saltare da una linea X alla successiva (1 / |ray_dir_x|)
	double	delta_y;   // Distanza che il raggio deve percorrere per saltare da una linea Y alla successiva (1 / |ray_dir_y|)
	double	side_x;    // Distanza dal punto di partenza del raggio al primo incrocio con una linea X (verticale)
	double	side_y;    // Distanza dal punto di partenza del raggio al primo incrocio con una linea Y (orizzontale)
	int		step_x;    // Direzione in cui il raggio salta sulla griglia X (-1 per ovest, +1 per est)
	int		step_y;    // Direzione in cui il raggio salta sulla griglia Y (-1 per nord, +1 per sud)
	int		hit;       // Flag di collisione: 0 = il raggio sta viaggiando, 1 = il raggio ha colpito un muro ('1')
	int		side;      // Indica quale lato del muro è stato colpito: 0 = lato Est/Ovest (X), 1 = lato Nord/Sud (Y)
	double	perp_wall_dist; // La distanza proiettata perpendicolarmente
}	t_ray;

/* ==================== VETTORI ==================== */
/* ** Struttura base per memorizzare coordinate o direzioni con alta precisione (double).
*/
typedef struct s_vector
{
	double	x; //asse x del vettore
	double	y; //asse y del vettore
}	t_vector;

/* ==================== GRAPHICS (MLX) ==================== */
/* ** Struttura standard richiesta dalla MiniLibX per gestire un'immagine
** in memoria prima di "spingerla" sullo schermo (tecnica del double buffering).
*/
typedef struct s_img
{
	void	*img;            // Puntatore opaco all'oggetto immagine creato da mlx_new_image
	char	*addr;           // Indirizzo di memoria (array di pixel) dove si va a scrivere il colore
	int		bits_per_pixel;  // Quanti bit servono per descrivere un pixel (solitamente 32, ovvero 4 byte ARGB)
	int		line_length;     // Quanti byte occupa una singola riga orizzontale dell'immagine in memoria
	int		endian;          // Ordine dei byte in memoria (0 = Little Endian, 1 = Big Endian)
}	t_img;

/*
** Contiene i percorsi (path) dei file .xpm per le texture dei muri,
** estratti durante il parsing del file .cub.
*/
typedef struct s_textures
{
	char	*north; // Percorso dell'immagine per i muri esposti a Nord
	char	*south; // Percorso dell'immagine per i muri esposti a Sud
	char	*west; // Percorso dell'immagine per i muri esposti a Ovest
	char	*east; // Percorso dell'immagine per i muri esposti a Est
}	t_textures;

/*
** Struttura per memorizzare i valori RGB letti dal file .cub
** per colorare il pavimento o il soffitto.
*/
typedef struct s_color
{
	int	r; // Valore Rosso (Red) da 0 a 255
	int	g; // Valore Verde (Green) da 0 a 255
	int	b; // Valore Blu (Blue) da 0 a 255
}	t_color;

/*
** Struttura che contiene i dati essenziali della mappa giocabile.
*/
typedef struct s_map
{
	char	**grid;  // Matrice bidimensionale di caratteri ('1' = muro, '0' = vuoto, ecc.) che rappresenta la mappa
	int		width;   // Larghezza massima della mappa (utile per controllare i fuori limite durante il DDA)
	int		height;  // Altezza totale della mappa (numero di righe)
}	t_map;

/* ==================== PLAYER (Updated) ==================== */
/*
** Tutte le informazioni fisiche relative al giocatore (la telecamera).
*/
typedef struct s_player
{
	t_vector	pos;       // Posizione esatta (X, Y) del giocatore all'interno della griglia (usa double per il movimento fluido)
	t_vector	dir;       // Vettore direzione: indica in che direzione (angolo) sta guardando il giocatore (lunghezza fissa = 1)
	t_vector	plane;     // Vettore piano telecamera: è perpendicolare alla direzione e definisce la larghezza del campo visivo (FOV)
	char		spawn_dir; // Carattere iniziale ('N', 'S', 'E', 'W') trovato sulla mappa durante il parsing
}	t_player;

/*
** Struttura principale "contenitore". È l'unica che viene passata 
** in giro per le funzioni (spesso come 'game') per avere accesso a tutto.
*/
typedef struct s_game
{
	void		*mlx;         // Puntatore all'istanza principale della libreria MLX (la connessione col server grafico)
	void		*window;      // Puntatore alla finestra vera e propria creata sullo schermo
	t_img		ghost_image;  // L'immagine "buffer" su cui si disegna ogni frame prima di mostrarlo (per evitare sfarfallii)
	t_textures	textures;     // Struct annidata contenente i percorsi stringa delle 4 texture
	t_color		floor;        // Struct annidata contenente i valori RGB del pavimento
	t_color		ceiling;      // Struct annidata contenente i valori RGB del soffitto
	int			floor_set;    // Flag (0/1) per sapere se il colore del pavimento è già stato letto e salvato correttamente
	int			ceiling_set;  // Flag (0/1) per sapere se il colore del soffitto è già stato letto e salvato correttamente
	t_map		map;          // Struct annidata contenente la griglia della mappa e le sue dimensioni
	t_player	player;       // Struct annidata contenente posizione, direzione e piano (FOV) del giocatore
    // TODO: Aggiungere array/struct per memorizzare i dati estratti (t_img) delle 4 texture caricate
}	t_game;

/* PROTOTIPI */

/* PARSING  */
/* File */
void	parse_file(t_game *game, char *filename);

/* Line checks */
int		is_empty_line(char *line);
int		is_map_line(char *line);
int		is_textures_line(char *line);
int		is_color_line(char *line);

/* Parsing elements */
void	parse_textures(t_game *game, char *line);
void	parse_color(t_game *game, char *line);
void	parse_rgb(char *str, t_color *color);
void	parse_map(t_game *game, char *line);
char	**resize_map(char **old, int new_size);

/* Utils */
char	*skip_spaces(char *str);
int		close_game(t_game *game);
int		key_press(int keycode, t_game *game);

/* Validation */
int		is_valid_map_char(char c);
void	validate_map(t_game *game);
bool    check_map_8neighbors(t_game *game);

/* ==================== GRAPHICS ==================== */
void	init_engine(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		close_game(t_game *game);
int		handle_keypress(int key, t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* ==================== MINIMAP ==================== */
void	draw_square(t_game *game, t_vector pos, int size, int color);
void	draw_minimap(t_game *game);
void	draw_player_2d(t_game *game);
void	test_ray_2d(t_game *game, int x);
void	draw_ray_line_2d(t_game *game, t_ray *ray);

void	apply_movement(t_game *game, double move_x, double move_y);
int		handle_keypress(int key, t_game *game);
void	rotate_player(t_game *game, double rot_dir);
int 	render_frame(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	set_step_and_side_dist(t_game *game, t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
void	draw_wall_column(t_game *game, t_ray *ray, int x);

/* ==================== LIBFT / GNL ==================== */
char	*get_next_line(int fd);

/* ==================== UTILS ==================== */
void 	error_exit(char *msg, t_game *game);
void	free_map(t_game *game);
void	free_textures(t_game *game);
char	*ft_strdup(const char *s);
char	*ft_strtrim(const char *s1, const char *set);

#endif
