/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 15:54:23 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/26 18:44:49 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"
#define WIDTH 512
#define HEIGHT 512
#define BPP 4

static mlx_image_t	*g_img;

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	hook(void* param)
{
	mlx_t* mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	for (unsigned int x = 0; x < g_img->width; x++)
		for(unsigned int y= 0; y < g_img->height; y++)
			mlx_put_pixel(g_img, x, y, rand() % RAND_MAX);
}


int	main(int argc, char **argv)
{	
	t_data		dat;
	mlx_t		*mlx;

	dat.str = valid_check(argc, argv, &dat.nodes, &dat.width);
	alloc_nodes(&dat);
	print_map(&dat);
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", false);
	if (!mlx)
		ft_error();
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!g_img)
		ft_error();
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
