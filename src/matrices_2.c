/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:46:10 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/10 15:47:35 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

void	translate_coords(t_data *dat, t_coords **con, int xs, int ys, int zs)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		con[y][x].x += xs;
		con[y][x].y += ys;
		con[y][x].z += zs;
		i++;
	}
}

void	set_matrix_identity(double mat[4][4])
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < 4)
	{
		while (x < 4)
		{
			if (y == x)
				mat[y][x] = 1;
			else
				mat[y][x] = 0;
			x++;
		}
		x = 0;
		y++;
	}
}

void	copy_coords(t_data *dat, t_coords **src, t_coords **dest)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		dest[y][x] = src[y][x];
		i++;
	}
}
