/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_coords.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:40:39 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/01 14:45:07 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

static t_coords	calc_coords(t_data *dat, int i)
{
	static int	j = 0;
	char		str_num[12];
	int			strpos;
	int			numflag;
	t_coords	new;

	strpos = 0;
	numflag = 0;
	new.x = i % dat->width * 10;
	new.y = i / dat->width * 10;
	while (1)
	{
		if (dat->str[j] == '-' || dat->str[j] == '+' || ft_isdigit(dat->str[j]))
		{
			str_num[strpos] = dat->str[j];
			strpos++;
			numflag = 1;
		}
		else if (numflag == 1 && !ft_isdigit(dat->str[j]))
		{
			str_num[strpos] = '\0';
			break ;
		}
		j++;
	}
	new.z = ft_atoi(str_num);
	return (new);
}

void	alloc_nodes(t_data *dat)
{
	t_coords	*new;
	int			i;

	new = malloc(sizeof(t_coords) * dat->nodes);
	if (new == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < dat->nodes)
	{
		new[i] = calc_coords(dat, i);
		i++;
	}
	dat->cor = new;
	// dat->mlx = mlx_init(WIDTH, HEIGHT, "FdF", false);
	// dat->img = mlx_new_image(dat->mlx, WIDTH, HEIGHT);
}
