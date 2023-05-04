/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:54:23 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/04 16:12:12 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"
#include <time.h> // ILLEGAL!!1
#define BPP 4

// void	rotate_plane_y(t_data *dat, double rad)
// {
// 	double	m[4][4];

// 	m[0][0] = cos(rad);
// }

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
	translate_coords(&dat, WIDTH / 2, HEIGHT / 2, 0);
	place_pixels(&dat);
	mlx_loop(dat.mlx);
	mlx_terminate(dat.mlx);
	return (0);
}
