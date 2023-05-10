/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:09:32 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/10 19:28:57 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

bool	draw_valid_px(mlx_image_t *img, int x, int y, int color); // rendering

void	draw_line(t_data *dat, t_intcor c0, t_intcor c1)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;

	dx = abs(c1.x - c0.x);
	dy = -abs(c1.y - c0.y);
	sx = -1;
	sy = -1;
	if (c0.x < c1.x)
		sx = 1;
	if (c0.y < c1.y)
		sy = 1;
	err = dx + dy;
	while (1)
	{
		draw_valid_px(dat->img, c0.x, c0.y, COL_WHT);
		if (c0.x == c1.x && c0.y == c1.y)
			break ;
		err2 = 2 * err;
		if (err2 >= dy)
		{
			err += dy;
			c0.x += sx;
		}
		if (err2 <= dx)
		{
			err += dx;
			c0.y += sy;
		}
	}
}


