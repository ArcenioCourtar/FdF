/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_coords_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:46:12 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/24 18:40:38 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

static uint32_t	pos_high(double z, int zmax)
{
	uint32_t	res1;
	uint32_t	res2;

	res1 = z * 255 / zmax;
	res2 = (zmax - z) * 255 / zmax;
	return (get_color(res1, res2, 0, 255));
}

static uint32_t	pos_low(double z, int zmin)
{
	uint32_t	res1;
	uint32_t	res2;

	res1 = z * 255 / zmin;
	res2 = (zmin - z) * 255 / zmin;
	return (get_color(0, res2, res1, 255));
}

void	color_height(t_data *dat)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	while (i < dat->nodes)
	{
		y = i / dat->width;
		x = i % dat->width;
		if (dat->cor[y][x].z > 0)
			dat->cor[y][x].color = pos_high(dat->cor[y][x].z, dat->zmax);
		else if (dat->cor[y][x].z < 0)
			dat->cor[y][x].color = pos_low(dat->cor[y][x].z, dat->zmin);
		else
			dat->cor[y][x].color = COL_GRN;
		i++;
	}
}
