#ifndef CUB3D_H
# define CUB3D_H
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05
# define TILE_SIZE 64

/* ==================== LIBRARIES ==================== */
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

/* ==================== STRUCTS ==================== */

/* ==================== RAGGI ====================== */
typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_y;
	int		map_x;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;


/* ==================== VETTORI ==================== */
typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

/* ==================== GRAPHICS (MLX) ==================== */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_textures;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

/* ==================== PLAYER (Updated) ==================== */
typedef struct s_player
{
	t_vector	pos;      // Sostituiamo int x, y con t_vector (double)
	t_vector	dir;      // Vettore direzione
	t_vector	plane;    // Vettore piano camera (FOV)
	char		spawn_dir; // 'N', 'S', 'E', 'W' salvato dal parsing
}	t_player;

typedef struct s_game
{
	void	*mlx; //libreria grafica minilibx
	void	*window; // finestra
	t_img	ghost_image; //immagine fantasma su cui disegnare
	t_textures	textures;
	t_color		floor;
	t_color		ceiling;
	int			floor_set;
	int			ceiling_set;
	t_map		map;
	t_player	player;
	// Aggiungi qui le immagini caricate per NO, SO, WE, EA dopo
}	t_game;

/* ==================== PARSING ==================== */

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
void	validate_map(t_game *game);

/* raycasting */
void	init_engine(t_game *game);
int 	render_frame(t_game *game);
void    my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_ray(t_game *g);

/* ==================== LIBFT / GNL ==================== */
char	*get_next_line(int fd);

/* ==================== UTILS ==================== */
void 	error_exit(char *msg, t_game *game);
void    free_game(t_game *game);
char	*ft_strdup(const char *s);
char	*ft_strtrim(const char *s1, const char *set);

#endif