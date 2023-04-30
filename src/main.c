/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:54:23 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/30 13:13:38 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"
#define BPP 4

/*
	NO GLOBAL VARIABLES!!!!!
*/
int	main(int argc, char **argv)
{	
	t_data		dat;

	dat.str = valid_check(argc, argv, &dat.nodes, &dat.width);
	alloc_nodes(&dat);
	print_map(&dat);
	mlx_loop(dat.mlx);
	mlx_terminate(dat.mlx);
	return (0);
}
