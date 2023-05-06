/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:49:11 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/06 19:38:21 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define BPP		4
# define BUFFSIZ	1000
# define WIDTH		1024
# define HEIGHT		1024
# define COL_WHT	0xFFFFFFFFu
# define COL_RED	0xFF0000FFu
# define COL_GRN	0x00FF00FFu
# define COL_BLU	0x0000FFFFu
# define COL_YEL	0xFFFF00FFu
# define COL_BLK	0x000000FFu
# include "MLX42/MLX42.h"
# include <stddef.h>
# include <math.h>		// all math functions
# include <fcntl.h>		// open()
# include <unistd.h>	// close(), read(), write()
# include <stdlib.h>	// malloc(), free(), exit()
# include <stdio.h>		// perror()
# include <string.h>	// strerror()

typedef struct s_data {
	mlx_t			*mlx;
	mlx_image_t		*img;
	struct s_coords	**cor;
	struct s_coords	**rot;
	struct s_coords	**cam;
	char			*str;
	int				nodes;
	int				width;
	double			mat[4][4];
}	t_data;

typedef struct s_coords {
	double	x;
	double	y;
	double	z;
	double	w;
}	t_coords;

typedef enum e_mat {
	ROT_X,
	ROT_Y,
	ROT_Z
}	t_mat;

char	*valid_check(int argc, char **argv, int *nodes, int *width);
void	alloc_nodes(t_data *dat);
void	set_matrix_identity(double mat[4][4]);
void	rot_points(t_data *dat, double rad, t_mat rot);
void	translate_coords(t_data *dat, t_coords **con, int tr[3]);
void	place_pixels(t_data *dat, int color);
void	convert_3d_2d(t_data *dat);
void	fill_image(t_data *dat, int color);
void	draw_line(t_data *dat, int x0, int y0, int x1, int y1, int color);
void	copy_coords(t_data *dat, t_coords **src, t_coords **dest);
void	connect_points(t_data *dat);

// debug functions
void	debug_print_coords(t_data const *dat);
void	debug_print_map(t_data const *dat);
void	debug_print_info(t_data const *dat);

#endif