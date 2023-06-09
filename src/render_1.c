/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:02:58 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/17 18:28:04 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

// Checks if the pixel position requested is within the bounds of our image.
// If not, don't draw the pixel.
bool	draw_valid_px(mlx_image_t *img, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && (uint32_t)x < img->width \
	&& (uint32_t)y < img->height)
	{
		mlx_put_pixel(img, x, y, color);
		return (true);
	}
	return (false);
}

// If all the color values for RGB are the same, memset.
// Then check if A has a different value. If it does, do a second memset pass.
// If not, do nothing.
static void	fill_memset(t_data *dat, int color)
{
	uint32_t	i;

	ft_memset(dat->img->pixels, (color >> 24) & 0xFF, dat->img->width \
	* dat->img->height * BPP);
	i = 3;
	if ((color & 0xFF) != ((color >> 24) & 0xFF))
	{
		while (i < dat->img->width * dat->img->height * BPP)
		{
			ft_memset(dat->img->pixels + i, color & 0xFF, 1);
			i += 4;
		}
	}
}

// Fill background with a single color.
// In case the byte values for RGB are all the same, perform a single memset()
// call, otherwise use put_pixel() for each pixel on the screen
void	fill_image(t_data *dat, int color)
{
	uint32_t	x;
	uint32_t	y;

	if (((color >> 8) & 0xFF) == ((color >> 16) & 0xFF) \
	&& ((color >> 8) & 0xFF) == ((color >> 24) & 0xFF))
		return (fill_memset(dat, color));
	x = 0;
	y = 0;
	while (y < dat->img->height)
	{
		while (x < dat->img->width)
		{
			mlx_put_pixel(dat->img, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
}
