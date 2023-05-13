/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:54:23 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/13 14:24:49 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

void	hook_keys(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

/*
	NO GLOBAL VARIABLES!!!!!
	56 byte leak after calling mlx_terminate() (on WSL at least). why?
*/
int	main(int argc, char **argv)
{	
	t_data		dat;

	dat.str = valid_check(argc, argv, &dat.nodes, &dat.width);
	alloc_nodes(&dat);
	mlx_image_to_window(dat.mlx, dat.img, 0, 0);
	rot_points(&dat, dat.cor, asin(tan(M_PI / 5)), AXIS_Z);
	rot_points(&dat, dat.rot, M_PI / 4, AXIS_X);
	convert_3d_2d(&dat);
	move_coords_within_screen(&dat);
	fill_image(&dat, COL_BLK);
	connect_points(&dat);
	mlx_loop_hook(dat.mlx, hook_keys, dat.mlx);
	mlx_loop(dat.mlx);
	mlx_terminate(dat.mlx);
	exit(EXIT_SUCCESS);
}
