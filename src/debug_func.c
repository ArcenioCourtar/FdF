/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:42:09 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/04 11:57:38 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

void	debug_print_coords(t_data const *dat)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < dat->nodes / dat->width)
	{
		while (j < dat->width)
		{
			ft_printf("n: %i, index: %ix%i, x: %i, y: %i, z: %i\n", \
			(i * dat->width + j), i, j, (int)dat->cor[i][j].x, (int)dat->cor[i][j].y, \
			(int)dat->cor[i][j].z);
			j++;
		}
		j = 0;
		i++;
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
