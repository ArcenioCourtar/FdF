/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_coords.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:40:39 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/20 17:45:42 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

/*
	Assigns values to each node, and checks for oevrflows.
	Might need some extra checking at the end of it all.
*/
static void	assign_coords(t_coords *new, int x, int y, char const *str)
{
	long	tmp;

	tmp = x * DISTX;
	if (tmp > INT_MAX || tmp < INT_MIN)
		msg_exit("int overflow\n", false);
	new->x = tmp;
	tmp = y * DISTY;
	if (tmp > INT_MAX || tmp < INT_MIN)
		msg_exit("int overflow\n", false);
	new->y = tmp;
	tmp = ft_atol(str);
	if (tmp > INT_MAX || tmp < INT_MIN)
		msg_exit("int overflow\n", false);
	new->z = tmp;
}

// Sets up the string to atoi
static t_coords	calc_coords(t_data *dat, int x, int y)
{
	static int	s = 0;
	char		str_num[12];
	int			strpos;
	int			numflag;
	t_coords	new;

	strpos = 0;
	numflag = 0;
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
	assign_coords(&new, x, y, str_num);
	return (new);
}

// Allocate memory equal to the amount of x coords for each y coord
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

// Add correct coords to each node's coordinates.
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
			dat->rot[y][x] = dat->cor[y][x];
			x++;
		}
		x = 0;
		y++;
	}
}

void	color_default(t_data *dat)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < dat->nodes / dat->width)
	{
		while (x < dat->width)
		{
			dat->cor[y][x].color = COL_WHT;
			x++;
		}
		x = 0;
		y++;
	}
}

void	color_rand(t_data *dat)
{
	// uint32_t rnum;
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < dat->nodes / dat->width)
	{
		while (x < dat->width)
		{
			dat->cor[y][x].color = COL_RED;
			x++;
		}
		x = 0;
		y++;
	}
}

void	color_nodes(t_data *dat)
{
	if (dat->argc != 3)
		color_default(dat);
	else if (dat->argc == 3 && ft_strncmp(dat->argv[2], "RAINBOW", 7) == 0)
		color_rand(dat);
	else
		color_default(dat);
}

// Allocate memory for the nodes, and any other struct members.
// Start with allocating memory for pointers equal to the # of y coords.
// This ensures that I'm reading sequential memory when going through my data.
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
