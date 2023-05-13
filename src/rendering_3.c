/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:09:32 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/13 17:14:42 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

bool	draw_valid_px(mlx_image_t *img, int x, int y, int color); // rendering

void	draw_down(t_data *dat, t_intcor c0, t_intcor c1)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;
	int	y;
	int	x;
	// int	diff;

	dx = c1.x - c0.x;
	dy = c1.y - c0.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = (2 * dy) - dx;
	y = c0.y;
	x = c0.x;
	while (x < c1.x)
	{
		draw_valid_px(dat->img, x, y, c0.color);
		if (d > 0)
		{
			y += yi;
			d += 2 * (dy - dx);
		}
		else
			d += 2 * dy;
		x++;
	}
}

void	draw_up(t_data *dat, t_intcor c0, t_intcor c1)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;
	int	x;
	int	y;

	dx = c1.x - c0.x;
	dy = c1.y - c0.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	x = c0.x;
	y = c0.y;
	while (y < c1.y)
	{
		draw_valid_px(dat->img, x, y, c0.color);
		if (d > 0)
		{
			x += xi;
			d += 2 * (dx - dy);
		}
		else
			d += 2 * dx;
		y++;
	}
}

void	draw_line(t_data *dat, t_intcor c0, t_intcor c1)
{
	if (abs(c1.y - c0.y) < abs(c1.x - c0.x))
	{
		if (c0.x > c1.x)
			draw_down(dat, c1, c0);
		else
			draw_down(dat, c0, c1);
	}
	else
	{
		if (c0.y > c1.y)
			draw_up(dat, c1, c0);
		else
			draw_up(dat, c0, c1);
	}
}
