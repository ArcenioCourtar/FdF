/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:54:23 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/07 19:54:16 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

void	hook_keys(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	scale_coords(t_data *dat, t_lim lim)
{
	double	xscale;
	double	yscale;
	int		i;
	int		y;
	int		x;

	xscale = (double)WIDTH / (lim.xmax - lim.xmin);
	yscale = (double)HEIGHT / (lim.ymax - lim.ymin);
	i = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		if (xscale < yscale)
		{
			dat->cam[y][x].x = dat->cam[y][x].x * xscale;
			dat->cam[y][x].y = dat->cam[y][x].y * xscale;
		}
		else
		{
			dat->cam[y][x].x = dat->cam[y][x].x * yscale;
			dat->cam[y][x].y = dat->cam[y][x].y * yscale;
		}
		i++;
	}
}

void	move_coords_within_screen(t_data *dat)
{
	int		c[2];
	t_lim	lim;
	int		i;

	i = 0;
	c[1] = i % dat->width;
	c[0] = i / dat->width;
	lim.xmin = dat->cam[c[0]][c[1]].x;
	lim.xmax = dat->cam[c[0]][c[1]].x;
	lim.ymin = dat->cam[c[0]][c[1]].y;
	lim.ymax = dat->cam[c[0]][c[1]].y;
	while (i < dat->nodes)
	{
		c[1] = i % dat->width;
		c[0] = i / dat->width;
		if (dat->cam[c[0]][c[1]].x < lim.xmin)
			lim.xmin = dat->cam[c[0]][c[1]].x;
		if (dat->cam[c[0]][c[1]].x > lim.xmax)
			lim.xmax = dat->cam[c[0]][c[1]].x;
		if (dat->cam[c[0]][c[1]].y < lim.ymin)
			lim.ymin = dat->cam[c[0]][c[1]].y;
		if (dat->cam[c[0]][c[1]].y > lim.ymax)
			lim.ymax = dat->cam[c[0]][c[1]].y;
		i++;
	}
	translate_coords(dat, dat->cam, -lim.xmin, -lim.ymin, 0);
	scale_coords(dat, lim);
}

/*
	NO GLOBAL VARIABLES!!!!!
	transformation order: SCALE, ROTATE, TRANSLATE
*/
int	main(int argc, char **argv)
{	
	t_data		dat;

	// INITIAL WORK
	dat.str = valid_check(argc, argv, &dat.nodes, &dat.width);
	alloc_nodes(&dat);
	mlx_image_to_window(dat.mlx, dat.img, 0, 0);

	// MATRIX OPERATIONS
	rot_points(&dat, M_PI, ROT_Z);
	convert_3d_2d(&dat);
	move_coords_within_screen(&dat);

	// GRAPHICS
	fill_image(&dat, COL_BLK);
	connect_points(&dat);
	//place_pixels(&dat, COL_RED);

	// MLX
	mlx_loop_hook(dat.mlx, hook_keys, dat.mlx);
	mlx_loop(dat.mlx);
	mlx_terminate(dat.mlx);
	return (0);
}
