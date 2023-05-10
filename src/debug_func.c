/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:42:09 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/10 15:44:06 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

void	debug_print_coords(t_data const *dat)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < dat->nodes / dat->width)
	{
		while (x < dat->width)
		{
			ft_printf("n: %i, (y*x): %ix%i, x: %i, y: %i, z: %i\n", \
			(y * dat->width + x), y, x, (int)dat->cor[y][x].x, \
			(int)dat->cor[y][x].y, (int)dat->cor[y][x].z);
			x++;
		}
		x = 0;
		y++;
	}
}

void	debug_print_map(t_data const *dat)
{
	ft_printf("\n%s\n", dat->str);
}

void	debug_print_info(t_data const *dat)
{
	ft_printf("\nNodes: %i, width %i\n", dat->nodes, dat->width);
}
