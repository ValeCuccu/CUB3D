/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpastac <anpastac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:45:02 by vacuccu           #+#    #+#             */
/*   Updated: 2026/04/22 10:04:06 by anpastac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.02
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
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_textures
{
    char    *north;
    char    *south;
    char    *west;
    char    *east;
    char    *floor;
    char    *ceiling;
    t_img   n_tex;
    t_img   s_tex;
    t_img   w_tex;
    t_img   e_tex;
    t_img   f_tex;   // AGGIUNTA
    t_img   c_tex;   // AGGIUNTA
}   t_textures;

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
	int		ceiling_color;
	int		floor_color;
}	t_map;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	char		spawn_dir;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_img		ghost_image;
	t_textures	textures;
	int			floor_set;
	int			ceiling_set;
	t_map		map;
	t_player	player;
	char		*current_line;
	int			fd;
	int			keys[65365];
}	t_game;

void	parse_file(t_game *game, char *filename);
int		is_empty_line(char *line);
int		is_map_line(char *line);
int		is_textures_line(char *line);
int		is_color_line(char *line);

void	parse_textures(t_game *game, char *line);
void	parse_color(t_game *game, char *line);
void	parse_rgb(char *str, t_color *color);
void	parse_map(t_game *game, char *line);
char	**resize_map(t_game *game, char **old, int new_size);

char	*skip_spaces(char *str);
int		close_game(t_game *game);
int		rgb_to_int(t_color c);

int		is_valid_map_char(char c);
void	validate_map(t_game *game);
bool	check_map_8neighbors(t_game *game);
void	handle_player(t_game *game, t_point p, char c, int *count);
int		is_player(char c);
int		scan_map(t_game *game);
int		check_extension(char *file);

void	init_engine(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		close_game(t_game *game);
int		handle_keypress(int key, t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

void	draw_square(t_game *game, t_vector pos, int size, int color);
void	draw_minimap(t_game *game);
void	draw_player_2d(t_game *game);
void	perform_ray(t_game *game, int x);

void	apply_movement(t_game *game, double move_x, double move_y);
void	rotate_player(t_game *game, double rot_dir);
int		render_frame(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	set_step_and_side_dist(t_game *game, t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
void	draw_wall_column(t_game *game, t_ray *ray, int x);

void	draw_3d_projection(t_game *game, t_ray *ray, int x);

char	*get_next_line(int fd);

void	error_exit(char *msg, t_game *game);
void	cleanup_game(t_game *game);
void	free_map(t_game *game);
void	free_textures(t_game *game);
char	*ft_strdup(const char *s);
char	*ft_strtrim(const char *s1, const char *set);

int		key_press(int key, t_game *g);
int		key_release(int key, t_game *g);
void	update_player_state(t_game *game);

int		get_texture_pixel(t_img *tex, int x, int y);
t_img	*get_wall_texture(t_game *game, t_ray *ray);
int		calculate_tex_x(t_game *game, t_ray *ray, t_img *tex);

#endif