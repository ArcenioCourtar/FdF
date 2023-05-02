/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:54:23 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/02 23:07:41 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"
#include <time.h> // ILLEGAL!!1
#define BPP 4

void	vector_testing(t_data *dat)
{
	int		k;
	double	len;

	srand(time(NULL));
	k = rand() % dat->nodes;
	k = 0;
	printf("Node %i: %f, %f, %f\n", k, dat->cor[k].x, dat->cor[k].y, dat->cor[k].z);
	len = 0;
	if (!(dat->cor[k].x == 0 && dat->cor[k].y == 0 && dat->cor[k].z == 0))
		len = sqrt(dat->cor[k].x * dat->cor[k].x + dat->cor[k].y * dat->cor[k].y + dat->cor[k].z * dat->cor[k].z);
	printf("vector len: %i, %f\n", (int)len, len);
}

t_coords	assign_val(int x, int y, int z)
{
	t_coords new;

	new.x = x;
	new.y = y;
	new.z = z;
}

/*
	NO GLOBAL VARIABLES!!!!!
*/
int	main(int argc, char **argv)
{	
	t_data		dat;
	t_coords	a, b, c;

	dat.str = valid_check(argc, argv, &dat.nodes, &dat.width);
	alloc_nodes(&dat);
	// debug_print_map(&dat);
	// vector_testing(&dat);
	// mlx_image_to_window(dat.mlx, dat.img, 0, 0);
	// mlx_loop(dat.mlx);
	// mlx_terminate(dat.mlx);
	return (0);
}
