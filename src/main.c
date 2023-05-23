/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:54:23 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/23 18:07:39 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

void	scale_coords(t_data *dat, double scale)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		dat->cam[y][x].x = dat->cam[y][x].x * scale;
		dat->cam[y][x].y = dat->cam[y][x].y * scale;
		i++;
	}
}

void	hook_keys(void *param)
{
	mlx_t	*mlx;
	t_data	*dat;

	dat = param;
	mlx = dat->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		translate_coords(dat, dat->cam, AXIS_Y, -2);
		fill_image(dat, COL_BLK);
		connect_points(dat);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		translate_coords(dat, dat->cam, AXIS_Y, 2);
		fill_image(dat, COL_BLK);
		connect_points(dat);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		translate_coords(dat, dat->cam, AXIS_X, 2);
		fill_image(dat, COL_BLK);
		connect_points(dat);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		translate_coords(dat, dat->cam, AXIS_X, -2);
		fill_image(dat, COL_BLK);
		connect_points(dat);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		scale_coords(dat, 1.01);
		fill_image(dat, COL_BLK);
		connect_points(dat);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		scale_coords(dat, 0.99);
		fill_image(dat, COL_BLK);
		connect_points(dat);
	}
}

int	main(int argc, char **argv)
{	
	t_data		dat;

	valid_check(argc, argv, &dat);
	alloc_nodes(&dat);
	mlx_image_to_window(dat.mlx, dat.img, 0, 0);
	rot_points(&dat, dat.cor, asin(tan(M_PI / 5)), AXIS_Z);
	rot_points(&dat, dat.rot, M_PI / 4, AXIS_X);
	convert_3d_2d(&dat);
	move_coords_within_screen(&dat);
	fill_image(&dat, COL_BLK);
	connect_points(&dat);
	mlx_loop_hook(dat.mlx, hook_keys, &dat);
	mlx_loop(dat.mlx);
	mlx_terminate(dat.mlx);
	exit(EXIT_SUCCESS);
}
