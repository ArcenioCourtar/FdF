/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:54:23 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/04 16:53:45 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"
#include <time.h> // ILLEGAL!!1
#define BPP 4

void	matrix_mult(double m[4][4], t_data *dat, int i)
{
	int			x;
	int			y;
	t_coords	tmp;

	x = i % dat->width;
	y = i / dat->width;
	tmp = dat->rot[y][x];
	dat->rot[y][x].x = m[0][0] * tmp.x + m[0][1] * tmp.y + m[0][2] * tmp.z;
	dat->rot[y][x].y = m[1][0] * tmp.x + m[1][1] * tmp.y + m[1][2] * tmp.z;
	dat->rot[y][x].z = m[2][0] * tmp.x + m[2][1] * tmp.y + m[2][2] * tmp.z;
}

void	rotate_plane_y(t_data *dat, double rad)
{
	double	m[4][4];
	int		i;

	m[0][0] = cos(rad);
	m[0][1] = -sin(rad);
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = sin(rad);
	m[1][1] = cos(rad);
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
	i = 0;
	while (i < dat->nodes)
	{
		matrix_mult(m, dat, i);
		i++;
	}
}

void	translate_coords(t_data *dat, int sx, int sy, int sz)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		dat->rot[y][x].x += sx;
		dat->rot[y][x].y += sy;
		dat->rot[y][x].z += sz;
		dat->rot[y][x].w = 1;
		i++;
	}
}

void	place_pixels(t_data *dat)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		if (dat->rot[y][x].x >= 0 && dat->rot[y][x].y >= 0 && \
		dat->rot[y][x].x <= WIDTH && dat->rot[y][x].y <= HEIGHT)
			mlx_put_pixel(dat->img, dat->rot[y][x].x, dat->rot[y][x].y, COL_WHT);
		i++;
	}
}

/*
	NO GLOBAL VARIABLES!!!!!
	transformation order: SCALE, ROTATE, TRANSLATE
*/
int	main(int argc, char **argv)
{	
	t_data		dat;

	dat.str = valid_check(argc, argv, &dat.nodes, &dat.width);
	alloc_nodes(&dat);
	debug_print_coords(&dat);
	mlx_image_to_window(dat.mlx, dat.img, 0, 0);
	rotate_plane_y(&dat, M_PI_4);
	translate_coords(&dat, WIDTH / 2, 0, 0);
	place_pixels(&dat);
	mlx_loop(dat.mlx);
	mlx_terminate(dat.mlx);
	return (0);
}
