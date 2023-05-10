/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:41:38 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/10 16:39:29 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

static void	set_matrix_axis_x(double mat[4][4], double rad)
{
	mat[1][1] = cos(rad);
	mat[1][2] = -sin(rad);
	mat[2][1] = sin(rad);
	mat[2][2] = cos(rad);
}

static void	set_matrix_axis_y(double mat[4][4], double rad)
{
	mat[0][0] = cos(rad);
	mat[2][0] = -sin(rad);
	mat[0][2] = sin(rad);
	mat[2][2] = cos(rad);
}

static void	set_matrix_axis_z(double mat[4][4], double rad)
{
	mat[0][0] = cos(rad);
	mat[0][1] = -sin(rad);
	mat[1][0] = sin(rad);
	mat[1][1] = cos(rad);
}

static void	matrix_mult(t_data *dat, t_coords **src, int i)
{
	int			x;
	int			y;
	t_coords	tmp;

	x = i % dat->width;
	y = i / dat->width;
	tmp = src[y][x];
	dat->rot[y][x].x = dat->mat[0][0] * tmp.x + dat->mat[0][1] * tmp.y \
	+ dat->mat[0][2] * tmp.z;
	dat->rot[y][x].y = dat->mat[1][0] * tmp.x + dat->mat[1][1] * tmp.y \
	+ dat->mat[1][2] * tmp.z;
	dat->rot[y][x].z = dat->mat[2][0] * tmp.x + dat->mat[2][1] * tmp.y \
	+ dat->mat[2][2] * tmp.z;
}

void	rot_points(t_data *dat, t_coords **src, double rad, t_mat rot)
{
	void	(*mat_func[3])(double [4][4], double);
	int		i;

	mat_func[AXIS_X] = set_matrix_axis_x;
	mat_func[AXIS_Y] = set_matrix_axis_y;
	mat_func[AXIS_Z] = set_matrix_axis_z;
	set_matrix_identity(dat->mat);
	mat_func[rot](dat->mat, rad);
	i = 0;
	while (i < dat->nodes)
	{
		matrix_mult(dat, src, i);
		i++;
	}
}
