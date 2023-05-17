/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:09:32 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/17 16:08:00 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

bool	draw_valid_px(mlx_image_t *img, int x, int y, int color); // rendering
void	draw_down(t_data *dat, t_intcor c0, t_intcor c1);
void	draw_up(t_data *dat, t_intcor c0, t_intcor c1); // drawline_help

static void	draw_line(t_data *dat, t_intcor c0, t_intcor c1)
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

static void	assign_intcor(t_coords **coords, t_intcor *c, int y, int x)
{
	c->x = coords[y][x].x;
	c->y = coords[y][x].y;
	c->color = coords[y][x].color;
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
