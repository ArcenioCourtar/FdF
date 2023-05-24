/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:46:10 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/24 19:44:01 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

// Perform translation on coordinates along a specific axis.
void	translate_coords(t_data *dat, t_coords **con, t_mat rot, int t)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		if (rot == AXIS_X)
			con[y][x].x += t;
		else if (rot == AXIS_Y)
			con[y][x].y += t;
		else if (rot == AXIS_Z)
			con[y][x].z += t;
		i++;
	}
}

// Reset the rotation matrix to an identity matrix.
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

// No actual conversion to 2d is happening here anymore, 
// since the rotations prior already result in the correct projection.
// It's still useful for keeping my "real" rotation coords and 
// "screen" coords separate.
void	convert_3d_2d(t_data *dat)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < dat->nodes)
	{
		x = i % dat->width;
		y = i / dat->width;
		dat->cam[y][x].x = dat->rot[y][x].x;
		dat->cam[y][x].y = dat->rot[y][x].y;
		dat->cam[y][x].z = dat->rot[y][x].z;
		dat->cam[y][x].color = dat->cor[y][x].color;
		i++;
	}
}
