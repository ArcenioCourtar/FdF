/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_coords.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:40:39 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/04 14:13:16 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

/*
	TODO: implement overflow/underflow checks here?
*/
static t_coords	calc_coords(t_data *dat, int i, int j)
{
	static int	s = 0;
	char		str_num[12];
	int			strpos;
	int			numflag;
	t_coords	new;

	strpos = 0;
	numflag = 0;
	new.x = i * 10;
	new.y = j * 10;
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
	int			i;
	int			j;

	new = malloc(sizeof(t_coords *) * (dat->nodes / dat->width));
	if (new == NULL)
		exit(EXIT_FAILURE);
	rot = malloc(sizeof(t_coords *) * (dat->nodes / dat->width));
	if (rot == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < dat->nodes / dat->width)
	{
		new[i] = malloc(sizeof(t_coords) * dat->width);
		if (new == NULL)
			exit(EXIT_FAILURE);
		rot[i] = malloc(sizeof(t_coords) * dat->width);
		if (rot == NULL)
			exit(EXIT_FAILURE);
		i++;
	}
	i = 0;
	j = 0;
	while (i < dat->nodes / dat->width)
	{
		while (j < dat->width)
		{
			new[i][j] = calc_coords(dat, i, j);
			rot[i][j] = new[i][j];
			j++;
		}
		j = 0;
		i++;
	}
	dat->cor = new;
	dat->rot = rot;
	dat->mlx = mlx_init(WIDTH, HEIGHT, "FdF", false);
	dat->img = mlx_new_image(dat->mlx, WIDTH, HEIGHT);
}
