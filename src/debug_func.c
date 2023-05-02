/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:42:09 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/01 12:01:56 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

void	debug_print_coords(t_data const *dat)
{
	int	i;

	i = 0;
	while (i < dat->nodes)
	{
		ft_printf("n: %i, x: %i, y: %i, z: %i\n", i, dat->cor[i].x, \
		dat->cor[i].y, dat->cor[i].z);
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
