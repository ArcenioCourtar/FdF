/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 10:49:11 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/25 19:10:36 by acourtar         ###   ########.fr       */
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
}	t_data;

typedef struct s_coords {
	int	x;
	int	y;
	int	z;
}	t_coords;
#endif