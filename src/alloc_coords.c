/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_coords.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:40:39 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/06 19:10:41 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

/*
	TODO: implement overflow/underflow checks here?
*/
static t_coords	calc_coords(t_data *dat, int x, int y)
{
	static int	s = 0;
	char		str_num[12];
	int			strpos;
	int			numflag;
	t_coords	new;

	strpos = 0;
	numflag = 0;
	new.x = x * 10;
	new.y = y * 10;
	new.w = 1;
	while (1)
	{
		if (dat->str[s] == '-' || dat->str[s] == '+' || ft_isdigit(dat->str[s]))
		{
			str_num[strpos] = dat->str[s];
			strpos++;
			numflag = 1;
		}
		else if (numflag == 1 && !ft_isdigit(dat->str[s]))
		{
			str_num[strpos] = '\0';
			break ;
		}
		s++;
	}
	new.z = ft_atoi(str_num);
	return (new);
}

void	alloc_nodes(t_data *dat)
{
	t_coords	**new;
	t_coords	**rot;
	t_coords	**cam;
	int			y;
	int			x;

	new = malloc(sizeof(t_coords *) * (dat->nodes / dat->width));
	if (new == NULL)
		exit(EXIT_FAILURE);
	rot = malloc(sizeof(t_coords *) * (dat->nodes / dat->width));
	if (rot == NULL)
		exit(EXIT_FAILURE);
	cam = malloc(sizeof(t_coords *) * (dat->nodes / dat->width));
	if (cam == NULL)
		exit(EXIT_FAILURE);
	y = 0;
	while (y < dat->nodes / dat->width)
	{
		new[y] = malloc(sizeof(t_coords) * dat->width);
		if (new == NULL)
			exit(EXIT_FAILURE);
		rot[y] = malloc(sizeof(t_coords) * dat->width);
		if (rot == NULL)
			exit(EXIT_FAILURE);
		cam[y] = malloc(sizeof(t_coords) * dat->width);
		if (cam == NULL)
			exit(EXIT_FAILURE);
		y++;
	}
	y = 0;
	x = 0;
	while (y < dat->nodes / dat->width)
	{
		while (x < dat->width)
		{
			new[y][x] = calc_coords(dat, x, y);
			rot[y][x] = new[y][x];
			x++;
		}
		x = 0;
		y++;
	}
	dat->cor = new;
	dat->rot = rot;
	dat->cam = cam;
	set_matrix_identity(dat->mat);
	dat->mlx = mlx_init(WIDTH, HEIGHT, "FdF", false);
	dat->img = mlx_new_image(dat->mlx, WIDTH, HEIGHT);
}
