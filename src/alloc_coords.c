/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_coords.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:40:39 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/13 14:27:51 by acourtar         ###   ########.fr       */
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
	new.x = x * 1;
	new.y = y * 1;
	while (1)
	{
		if (dat->str[s] == '-' || dat->str[s] == '+' || ft_isdigit(dat->str[s]))
		{
			str_num[strpos] = dat->str[s];
			strpos++;
			numflag = 1;
		}
		else if (numflag == 1 && !ft_isdigit(dat->str[s]))
			break ;
		s++;
	}
	str_num[strpos] = '\0';
	new.z = ft_atoi(str_num);
	return (new);
}

static void	alloc_rows(t_data *dat)
{
	int	y;

	y = 0;
	while (y < dat->nodes / dat->width)
	{
		dat->cor[y] = malloc(sizeof(t_coords) * dat->width);
		if (dat->cor[y] == NULL)
			exit(EXIT_FAILURE);
		dat->rot[y] = malloc(sizeof(t_coords) * dat->width);
		if (dat->rot[y] == NULL)
			exit(EXIT_FAILURE);
		dat->cam[y] = malloc(sizeof(t_coords) * dat->width);
		if (dat->cam[y] == NULL)
			exit(EXIT_FAILURE);
		y++;
	}
}

static void	fill_nodes(t_data *dat)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < dat->nodes / dat->width)
	{
		while (x < dat->width)
		{
			dat->cor[y][x] = calc_coords(dat, x, y);
			dat->cor[y][x].color = get_color(rand() % 255, rand() % 255, rand() % 255, 255);
			dat->rot[y][x] = dat->cor[y][x];
			x++;
		}
		x = 0;
		y++;
	}
}

void	alloc_nodes(t_data *dat)
{
	dat->cor = malloc(sizeof(t_coords *) * (dat->nodes / dat->width));
	if (dat->cor == NULL)
		exit(EXIT_FAILURE);
	dat->rot = malloc(sizeof(t_coords *) * (dat->nodes / dat->width));
	if (dat->rot == NULL)
		exit(EXIT_FAILURE);
	dat->cam = malloc(sizeof(t_coords *) * (dat->nodes / dat->width));
	if (dat->cam == NULL)
		exit(EXIT_FAILURE);
	alloc_rows(dat);
	fill_nodes(dat);
	set_matrix_identity(dat->mat);
	dat->mlx = mlx_init(WIDTH, HEIGHT, "FdF", false);
	dat->img = mlx_new_image(dat->mlx, WIDTH, HEIGHT);
}
