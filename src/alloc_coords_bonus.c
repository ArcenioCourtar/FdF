/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_coords_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:46:12 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/24 19:23:51 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

// These functions aren't needed but look more clean than handling the 
// calculations within get_color()
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

// BONUS
// If "HEIGHT" is passed as a third argument, ignores any possible
// colors in the map data and assigns height based on height.
// Anything with a Z value above 0 will color red, anything below 0 will
// be blue, increasing in intensity based on the highest/lowest Z coord.
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
