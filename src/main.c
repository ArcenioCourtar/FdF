/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:54:23 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/26 15:42:21 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

int	main(int argc, char **argv)
{	
	t_data	dat;

	dat.str = valid_check(argc, argv, &dat.nodes, &dat.width);
	ft_printf("map:\n%s|\nnodes: %i, width: %i\n", dat.str, dat.nodes, \
	dat.width);
	alloc_nodes(&dat);
	print_coords(&dat);
}
