/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:54:23 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/24 19:39:26 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

/*
	Program flow:
	Check if the arguments are valid, check if the map is a valid format.
	Allocate memory and calculate coords and color values (if any).
	Rotate calculated points to get them in isometric projection,
	Move these new coordinates within screen boundaries.
	Fill the mlx image with a single color, then connect all the points
	with a line drawing algorithm.
	mlx loop.
*/
int	main(int argc, char **argv)
{	
	t_data		dat;

	valid_check(argc, argv, &dat);
	alloc_nodes(&dat);
	mlx_image_to_window(dat.mlx, dat.img, 0, 0);
	rot_points(&dat, dat.cor, asin(tan(M_PI / 5)), AXIS_Z);
	rot_points(&dat, dat.rot, M_PI / 4, AXIS_X);
	convert_3d_2d(&dat);
	move_coords_within_screen(&dat);
	fill_image(&dat, COL_BLK);
	connect_points(&dat);
	mlx_loop_hook(dat.mlx, hook_keys, &dat);
	mlx_loop(dat.mlx);
	mlx_terminate(dat.mlx);
	exit(EXIT_SUCCESS);
}
