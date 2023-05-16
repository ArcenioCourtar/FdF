/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:09:32 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/16 18:25:48 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

bool	draw_valid_px(mlx_image_t *img, int x, int y, int color); // rendering

void	save_col(int col0, int col1, int col[2][4])
{
	col[0][0] = (col0 >> 24) & 0xFF;
	col[0][1] = (col0 >> 16) & 0xFF;
	col[0][2] = (col0 >> 8) & 0xFF;
	col[0][3] = (col0) & 0xFF;
	col[1][0] = (col1 >> 24) & 0xFF;
	col[1][1] = (col1 >> 16) & 0xFF;
	col[1][2] = (col1 >> 8) & 0xFF;
	col[1][3] = (col1) & 0xFF;
}

int	new_col(int col[2][4], int len, int i)
{
	int	new_col[4];

	new_col[0] = col[0][0] + ((col[1][0] - col[0][0]) * i / len);
	new_col[1] = col[0][1] + ((col[1][1] - col[0][1]) * i / len);
	new_col[2] = col[0][2] + ((col[1][2] - col[0][2]) * i / len);
	new_col[3] = col[0][3] + ((col[1][3] - col[0][3]) * i / len);
	return (new_col[0] << 24 | new_col[1] << 16 | new_col[2] << 8 | new_col[3]);
}

void	draw_down(t_data *dat, t_intcor c0, t_intcor c1)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;
	int	y;
	int	x;
	int	col[2][4];

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
	save_col(c0.color, c1.color, col);
	while (x < c1.x)
	{
		c0.color = new_col(col, c1.x - c0.x, x - c0.x);
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
	int	col[2][4];

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
	save_col(c0.color, c1.color, col);
	while (y < c1.y)
	{
		c0.color = new_col(col, c1.y - c0.y, y - c0.y);
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
