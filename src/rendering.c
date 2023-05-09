/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:02:58 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/09 19:36:48 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

bool	draw_valid_px(mlx_image_t *img, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && (uint32_t)x < img->width && (uint32_t)y < img->height)
	{
		mlx_put_pixel(img, x, y, color);
		return (true);
	}
	return (false);
}

void	place_pixels(t_data *dat, int color)
{
	int	i;
	int	x;
	int	y;
	int	pts;

	i = 0;
	pts = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		if (draw_valid_px(dat->img, dat->cam[y][x].x, dat->cam[y][x].y, color) == true)
			pts++;
		i++;
	}
	ft_printf("total pts: %i, pts on screen: %i\n", dat->nodes, pts);
}

void	convert_3d_2d(t_data *dat)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		dat->cam[y][x].x = dat->rot[y][x].x;
		dat->cam[y][x].y = dat->rot[y][x].y;
		dat->cam[y][x].z = dat->rot[y][x].z;
		i++;
	}
}

void	fill_image(t_data *dat, int color)
{
	unsigned int	x;
	unsigned int	y;
	//unsigned char	i = 0;

	x = 0;
	y = 0;
	while (y < dat->img->height)
	{
		while (x < dat->img->width)
		{
			mlx_put_pixel(dat->img, x, y, color);
			//color += (i & 0xFF) << 8;
			//i++;
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_line(t_data *dat, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;

	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = -1;
	sy = -1;
	if (x0 < x1)
		sx = 1;
	if (y0 < y1)
		sy = 1;
	err = dx + dy;
	while (1)
	{
		draw_valid_px(dat->img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		err2 = 2 * err;
		if (err2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (err2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	connect_points(t_data *dat)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		if (x < dat->width - 1)
			draw_line(dat, dat->cam[y][x].x, dat->cam[y][x].y, \
			dat->cam[y][x + 1].x, dat->cam[y][x + 1].y, COL_WHT);
		if (y < (dat->nodes / dat->width) - 1)
			draw_line(dat, dat->cam[y][x].x, dat->cam[y][x].y, \
			dat->cam[y + 1][x].x, dat->cam[y + 1][x].y, COL_WHT);
		i++;
	}
}
