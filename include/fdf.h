/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:49:11 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/26 16:05:04 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stddef.h>
# include <math.h>		// all math functions
# include <fcntl.h>		// open()
# include <unistd.h>	// close(), read(), write()
# include <stdlib.h>	// malloc(), free(), exit()
# include <stdio.h>		// perror()
# include <string.h>	// strerror()

typedef struct s_data {
	struct s_coords	*cor;
	char			*str;
	int				nodes;
	int				width;
}	t_data;

typedef struct s_coords {
	int	x;
	int	y;
	int	z;
}	t_coords;

char	*valid_check(int argc, char **argv, int *nodes, int *width);
void	alloc_nodes(t_data *dat);

// debug functions
void	print_coords(t_data const *dat);
void	print_map(t_data const *dat);
void	print_info(t_data const *dat);

#endif