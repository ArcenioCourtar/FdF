/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:54:23 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/06 19:54:21 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

/*
	NO GLOBAL VARIABLES!!!!!
	transformation order: SCALE, ROTATE, TRANSLATE
*/
int	main(int argc, char **argv)
{	
	t_data		dat;
	int			tr[3] = {WIDTH / 2, 0, 0};

	dat.str = valid_check(argc, argv, &dat.nodes, &dat.width);
	alloc_nodes(&dat);
	mlx_image_to_window(dat.mlx, dat.img, 0, 0);
	rot_points(&dat, M_PI / 4, ROT_Z);
	convert_3d_2d(&dat);
	translate_coords(&dat, dat.cam, tr);
	fill_image(&dat, COL_BLK);
	connect_points(&dat);
	place_pixels(&dat, COL_RED);
	mlx_loop(dat.mlx);
	mlx_terminate(dat.mlx);
	return (0);
}
