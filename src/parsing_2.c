/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:11:43 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/10 17:40:40 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

static void	column_check(int *col_max, int *col, int *width, int *i)
{
	if (*col_max == -1)
	{
		*col_max = *col;
		*width = *col_max;
	}
	else if (*col_max != *col)
		msg_exit("Column count error\n", false);
	*col = 0;
	(*i)++;
}

void	inc_count(char *str, int *i, int *col, int *total)
{
	if (*i == 0 || str[*i - 1] == ' ' || str[*i - 1] == '-' \
	|| str[*i - 1] == '+' || str[*i - 1] == '\n')
	{
		(*col)++;
		(*total)++;
	}
	(*i)++;
}

int	valid_map(char *str, int *width)
{
	int	i;
	int	col_max;
	int	col;
	int	total;

	i = 0;
	col_max = -1;
	col = 0;
	total = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			i++;
		else if ((str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1]))
			i++;
		else if (ft_isdigit(str[i]))
			inc_count(str, &i, &col, &total);
		else if (str[i] == '\n')
			column_check(&col_max, &col, width, &i);
		else
			msg_exit("incorrect format\n", false);
	}
	return (total);
}
