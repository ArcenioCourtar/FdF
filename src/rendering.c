/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:02:58 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/10 19:32:24 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

void	draw_line(t_data *dat, t_intcor c0, t_intcor c1); //_3

bool	draw_valid_px(mlx_image_t *img, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && (uint32_t)x < img->width \
	&& (uint32_t)y < img->height)
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

	i = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		draw_valid_px(dat->img, dat->cam[y][x].x, dat->cam[y][x].y, color);
		i++;
	}
}

void	fill_memset(t_data *dat, int color)
{
	uint32_t	i;

	ft_memset(dat->img->pixels, (color >> 24) & 0xFF, dat->img->width \
	* dat->img->height * BPP);
	i = 3;
	while (i < dat->img->width * dat->img->height * BPP)
	{
		ft_memset(dat->img->pixels + i, 255, 1);
		i += 4;
	}
}

void	fill_image(t_data *dat, int color)
{
	uint32_t	x;
	uint32_t	y;

	if (((color >> 8) & 0xFF) == ((color >> 16) & 0xFF) \
	&& ((color >> 8) & 0xFF) == ((color >> 24) & 0xFF))
		return (fill_memset(dat, color));
	x = 0;
	y = 0;
	while (y < dat->img->height)
	{
		while (x < dat->img->width)
		{
			mlx_put_pixel(dat->img, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
}

void	connect_points(t_data *dat)
{
	int			i;
	int			x;
	int			y;
	t_intcor	c0;
	t_intcor	c1;

	i = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		c0.x = dat->cam[y][x].x;
		c0.y = dat->cam[y][x].y;
		if (x < dat->width - 1)
		{
			c1.x = dat->cam[y][x + 1].x;
			c1.y = dat->cam[y][x + 1].y;
			draw_line(dat, c0, c1);
		}
		if (y < (dat->nodes / dat->width) - 1)
		{
			c1.x = dat->cam[y + 1][x].x;
			c1.y = dat->cam[y + 1][x].y;
			draw_line(dat, c0, c1);
		}
		i++;
	}
}
