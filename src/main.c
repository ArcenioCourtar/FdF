/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:54:23 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/06 16:03:47 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"
#include <time.h> // ILLEGAL!!1
#define BPP 4

/*
	NO GLOBAL VARIABLES!!!!!
	transformation order: SCALE, ROTATE, TRANSLATE
*/
int	main(int argc, char **argv)
{	
	t_data		dat;

	dat.str = valid_check(argc, argv, &dat.nodes, &dat.width);
	alloc_nodes(&dat);
	mlx_image_to_window(dat.mlx, dat.img, 0, 0);
	rot_points(&dat, M_PI / 4, ROT_Z);
	translate_coords(&dat, WIDTH / 2, 0, 0);
	place_pixels(&dat);
	mlx_loop(dat.mlx);
	mlx_terminate(dat.mlx);
	return (0);
}
