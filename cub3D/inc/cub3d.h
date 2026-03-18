/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 18:02:57 by vacuccu           #+#    #+#             */
/*   Updated: 2026/03/18 18:04:18 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		**map;        // Gestita da Antonio
	t_vector	pos;          // Gestita da Te
	t_vector	dir;          // Gestita da Te
	t_vector	plane;        // Il piano della camera (FOV)
	// Aggiungeremo qui i puntatori alle texture e colori
}	t_data;

#endif