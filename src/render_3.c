/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:09:32 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/29 18:43:20 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

bool	draw_valid_px(mlx_image_t *img, int x, int y, int color); // rendering
void	draw_gentle_slope(t_data *dat, t_dlcor c0, t_dlcor c1);
void	draw_steep_slope(t_data *dat, t_dlcor c0, t_dlcor c1); // drawline_help

// Change how I draw lines based on the distance between each y and x coord.
static void	draw_line(t_data *dat, t_dlcor c0, t_dlcor c1)
{
	if (abs(c1.x - c0.x) > abs(c1.y - c0.y))
	{
		if (c1.x > c0.x)
			draw_gentle_slope(dat, c0, c1);
		else
			draw_gentle_slope(dat, c1, c0);
	}
	else
	{
		if (c1.y > c0.y)
			draw_steep_slope(dat, c0, c1);
		else
			draw_steep_slope(dat, c1, c0);
	}
}

// Assign coordinates to struct used for line drawing algorithm
static void	assign_intcor(t_coords **coords, t_dlcor *c, int y, int x)
{
	c->x = coords[y][x].x;
	c->y = coords[y][x].y;
	c->color = coords[y][x].color;
}

// After finding the coordinates of all points, connect them with lines using
// Bresenham's line algorithm.
void	connect_points(t_data *dat)
{
	int			i;
	int			x;
	int			y;
	t_dlcor		c0;
	t_dlcor		c1;

	i = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		assign_intcor(dat->cam, &c0, y, x);
		if (x < dat->width - 1)
		{
			assign_intcor(dat->cam, &c1, y, x + 1);
			draw_line(dat, c0, c1);
		}
		if (y < (dat->nodes / dat->width) - 1)
		{
			assign_intcor(dat->cam, &c1, y + 1, x);
			draw_line(dat, c0, c1);
		}
		i++;
	}
}
