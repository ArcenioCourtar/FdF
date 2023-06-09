/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:29:59 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/17 18:01:59 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

// Print an error message, then exit the program.
void	msg_exit(const char *msg, bool useperr)
{
	if (useperr == true)
		perror(msg);
	else
		ft_printf("%s", msg);
	exit(EXIT_FAILURE);
}
