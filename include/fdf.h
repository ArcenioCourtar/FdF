/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:49:11 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/29 16:28:21 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define BPP		4
# define BUFFSIZ	10000 // large buffersize to speed up large map parsing
# define WIDTH		1024
# define HEIGHT		1024
# define DISTX		10
# define DISTY		10
# define COL_WHT	0xFFFFFFFFu
# define COL_RED	0xFF0000FFu
# define COL_GRN	0x00FF00FFu
# define COL_BLU	0x0000FFFFu
# define COL_GRY	0x888888FFu
# define COL_YEL	0xFFFF00FFu
# define COL_PUR	0xFF00FFFFu
# define COL_BLK	0x000000FFu
# include "MLX42/MLX42.h"
# include <stddef.h>
# include <float.h>		// defines related to doubles and floats
# include <limits.h>
# include <fcntl.h>		// open()
# include <unistd.h>	// close(), read(), write()
# include <stdlib.h>	// malloc(), free(), exit()
# include <stdio.h>		// perror()
# include <string.h>	// strerror()
# include <math.h>		// all math functions
# ifndef M_PI
#  define M_PI		3.14159265358979323846	/* pi */
# endif

// Main struct holding the mlx instance, mlx image,
// node coordinates, and any other important info related to my points.
typedef struct s_data {
	mlx_t			*mlx;
	mlx_image_t		*img;
	struct s_coords	**cor;
	struct s_coords	**rot;
	struct s_coords	**cam;
	char			*str;
	char			**argv;
	int				nodes;
	int				width;
	int				argc;
	int				zmax;
	int				zmin;
	double			mat[4][4];
}	t_data;

// Struct used to save the boundaries of the x and y coords on screen so
// the final image can be scaled up/down accordingly.
typedef struct s_lim {
	int	xmax;
	int	xmin;
	int	ymax;
	int	ymin;
}	t_lim;

// Struct used to store the coordinates and colors of the points passed to my
// line drawing functions.
typedef struct s_dlcor
{
	int			x;
	int			y;
	uint32_t	color;
}	t_dlcor;

// Struct holding the x, y and z coordinates, and colors of all my points.
typedef struct s_coords {
	double		x;
	double		y;
	double		z;
	uint32_t	color;
}	t_coords;

// Enum defining the axis we're rotating around.
typedef enum e_mat {
	AXIS_X,
	AXIS_Y,
	AXIS_Z
}	t_mat;

// Another struct used for the line drawing functions, all variables necessary
// are here.
typedef struct s_drawline {
	int	dx;
	int	dy;
	int	i;
	int	d;
	int	x;
	int	y;
}	t_drawline;

void		valid_check(int argc, char **argv, t_data *dat);
void		alloc_nodes(t_data *dat);
void		set_matrix_identity(double mat[4][4]);
void		rot_points(t_data *dat, t_coords **src, double rad, t_mat rot);
void		translate_coords(t_data *dat, t_coords **con, t_mat rot, int t);
void		convert_3d_2d(t_data *dat);
void		fill_image(t_data *dat, int color);
void		connect_points(t_data *dat);
void		move_coords_within_screen(t_data *dat);
void		msg_exit(const char *msg, bool useperr);
void		hook_keys(void *param);

uint32_t	get_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a);

#endif