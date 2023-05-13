/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:58:11 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/13 14:28:18 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

static void	scale_screen_coords(t_data *dat, t_lim lim)
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

static void	lim_calc(t_coords **cam, t_lim *lim, int y, int x)
{
	if (cam[y][x].x < lim->xmin)
		lim->xmin = cam[y][x].x;
	if (cam[y][x].x > lim->xmax)
		lim->xmax = cam[y][x].x;
	if (cam[y][x].y < lim->ymin)
		lim->ymin = cam[y][x].y;
	if (cam[y][x].y > lim->ymax)
		lim->ymax = cam[y][x].y;
}

void	move_coords_within_screen(t_data *dat)
{
	int		y;
	int		x;
	t_lim	lim;
	int		i;

	i = 0;
	x = i % dat->width;
	y = i / dat->width;
	lim.xmin = dat->cam[y][x].x;
	lim.xmax = dat->cam[y][x].x;
	lim.ymin = dat->cam[y][x].y;
	lim.ymax = dat->cam[y][x].y;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		lim_calc(dat->cam, &lim, y, x);
		i++;
	}
	translate_coords(dat, dat->cam, AXIS_X, -lim.xmin);
	translate_coords(dat, dat->cam, AXIS_Y, -lim.ymin);
	scale_screen_coords(dat, lim);
}

uint32_t	get_color(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
