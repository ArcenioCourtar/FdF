/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_coords.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:40:39 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/23 13:58:12 by acourtar         ###   ########.fr       */
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

static void	convert_hex_helper(t_coords *new, const char *str_hex, int len)
{
	int			i;
	int			j;
	uint32_t	result;
	char		*hex_chars;

	i = 0;
	result = 0;
	hex_chars = "0123456789ABCDEFabcdef";
	while (i < len)
	{
		j = 0;
		while (str_hex[i] != hex_chars[j])
			j++;
		if (j > 15)
			j -= 6;
		result += j * pow(16, 7 - i);
		i++;
	}
	while (i < 8)
	{
		result += 15 * pow(16, 7 - i);
		i++;
	}
	new->color = result;
}

static bool	valid_hex(t_coords *new, const char *str, int len)
{
	char	str_hex[9];
	int		i;

	if (len > 8 || len == 0)
		return (false);
	ft_memcpy(str_hex, str, len);
	str_hex[len] = '\0';
	i = 0;
	while (i < len)
	{
		if (ft_strchr("0123456789ABCDEFabcdef", str_hex[i]) == NULL)
			return (false);
		i++;
	}
	convert_hex_helper(new, str_hex, len);
	return (true);
}

static void	assign_col(t_coords *new, char *str, int *s)
{
	int	start;

	if (str[*s] != ',')
	{
		new->color = COL_WHT;
		(*s)++;
	}
	else
	{
		start = *s + 1;
		while (str[*s] != ' ' && str[*s] != '\0' && str[*s] != '\n')
			(*s)++;
		if (ft_strncmp(&str[start], "0x", 2) == 0)
		{
			if (!valid_hex(new, &str[start + 2], *s - start - 2))
				new->color = COL_WHT;
		}
		else
			new->color = COL_WHT;
	}
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
	assign_col(&new, dat->str, &s);
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

void	color_nodes(t_data *dat)
{
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
