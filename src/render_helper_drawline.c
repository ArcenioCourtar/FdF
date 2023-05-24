/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helper_drawline.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:43:58 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/24 19:51:19 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

bool	draw_valid_px(mlx_image_t *img, int x, int y, int color); // rendering

// Save the bytes representing the 4 color channels of the two points.
static void	save_col(int col0, int col1, int col[2][4])
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

// Calculate the color of each point in the lines by calculating the difference
// between each channel, then comparing how far along the line you are
static int	new_col(int col[2][4], int len, int i)
{
	int	new_col[4];

	if (len == 0)
	{
		new_col[0] = col[0][0];
		new_col[1] = col[0][1];
		new_col[2] = col[0][2];
		new_col[3] = col[0][3];
		return (new_col[0] << 24 | new_col[1] << 16 \
		| new_col[2] << 8 | new_col[3]);
	}
	new_col[0] = col[0][0] + ((col[1][0] - col[0][0]) * i / len);
	new_col[1] = col[0][1] + ((col[1][1] - col[0][1]) * i / len);
	new_col[2] = col[0][2] + ((col[1][2] - col[0][2]) * i / len);
	new_col[3] = col[0][3] + ((col[1][3] - col[0][3]) * i / len);
	return (new_col[0] << 24 | new_col[1] << 16 \
	| new_col[2] << 8 | new_col[3]);
}

// Initialize the values used for Bresenham's line algorithm.
static void	init_val(t_drawline *val, t_intcor c0, t_intcor c1, bool drawdown)
{
	val->dx = c1.x - c0.x;
	val->dy = c1.y - c0.y;
	val->i = 1;
	if (drawdown == true)
	{
		if (val->dy < 0)
		{
			val->i = -1;
			val->dy = -val->dy;
		}
		val->d = (2 * val->dy) - val->dx;
	}
	else
	{
		if (val->dx < 0)
		{
			val->i = -1;
			val->dx = -val->dx;
		}
		val->d = (2 * val->dx) - val->dy;
	}
	val->y = c0.y;
	val->x = c0.x;
}

// Algorithm for lines moving downward
void	draw_down(t_data *dat, t_intcor c0, t_intcor c1)
{
	t_drawline	val;
	int			col[2][4];

	init_val(&val, c0, c1, true);
	save_col(c0.color, c1.color, col);
	while (val.x < c1.x)
	{
		c0.color = new_col(col, c1.x - c0.x, val.x - c0.x);
		draw_valid_px(dat->img, val.x, val.y, c0.color);
		if (val.d > 0)
		{
			val.y += val.i;
			val.d += 2 * (val.dy - val.dx);
		}
		else
			val.d += 2 * val.dy;
		val.x++;
	}
}

// Algorithm for lines moving upward
void	draw_up(t_data *dat, t_intcor c0, t_intcor c1)
{
	t_drawline	val;
	int			col[2][4];

	init_val(&val, c0, c1, false);
	save_col(c0.color, c1.color, col);
	while (val.y < c1.y)
	{
		c0.color = new_col(col, c1.y - c0.y, val.y - c0.y);
		draw_valid_px(dat->img, val.x, val.y, c0.color);
		if (val.d > 0)
		{
			val.x += val.i;
			val.d += 2 * (val.dx - val.dy);
		}
		else
			val.d += 2 * val.dx;
		val.y++;
	}
}
