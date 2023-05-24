/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:32:10 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/24 19:34:46 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

// Scaling function used to zoom in and out on the wireframe
static void	scale_coords(t_data *dat, double scale)
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

// Lets you move the wireframe around the screen
static void	keys_movemap(mlx_t *mlx, t_data *dat)
{
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		translate_coords(dat, dat->cam, AXIS_Y, -4);
		fill_image(dat, COL_BLK);
		connect_points(dat);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		translate_coords(dat, dat->cam, AXIS_Y, 4);
		fill_image(dat, COL_BLK);
		connect_points(dat);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		translate_coords(dat, dat->cam, AXIS_X, 4);
		fill_image(dat, COL_BLK);
		connect_points(dat);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		translate_coords(dat, dat->cam, AXIS_X, -4);
		fill_image(dat, COL_BLK);
		connect_points(dat);
	}
}

// Lets you zoom in and out of the wireframe
static void	keys_zoommap(mlx_t *mlx, t_data *dat)
{
	static int	lim = 0;

	if (mlx_is_key_down(mlx, MLX_KEY_W) && lim < 200)
	{
		scale_coords(dat, 1.02);
		fill_image(dat, COL_BLK);
		connect_points(dat);
		lim++;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S) && lim > -200)
	{
		scale_coords(dat, 0.98);
		fill_image(dat, COL_BLK);
		connect_points(dat);
		lim--;
	}
}

// Hook that reads any potential keypresses
void	hook_keys(void *param)
{
	mlx_t	*mlx;
	t_data	*dat;

	dat = param;
	mlx = dat->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	keys_movemap(mlx, dat);
	keys_zoommap(mlx, dat);
}
