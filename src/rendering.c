/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:02:58 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/06 16:03:41 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

void	place_pixels(t_data *dat)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		if (dat->rot[y][x].x >= 0 && dat->rot[y][x].y >= 0 && \
		dat->rot[y][x].x <= WIDTH && dat->rot[y][x].y <= HEIGHT)
			mlx_put_pixel(dat->img, dat->rot[y][x].x, dat->rot[y][x].y, COL_WHT);
		i++;
	}
}
