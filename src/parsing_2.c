/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:11:43 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/24 19:50:31 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

// At the end of a row, checks the amount of columns counted.
// If this is the top row, col_max get set to the amount of cols counted.
// From that point onwards the amount of columns in each row get compared
// to the col_max to check for map validity.
static void	column_check(int *col_max, int *col, int *width, int *i)
{
	if (*col_max == -1)
	{
		*col_max = *col;
		*width = *col_max;
	}
	if (*col_max != *col)
		msg_exit("Column count error\n", false);
	*col = 0;
	(*i)++;
}

// skips any symbols found after the "," until another separator is found.
static void	skip_colors(char *str, int *i)
{
	while (str[*i] != ' ' && str[*i] != '\n' && str[*i] != '\0')
		(*i)++;
}

// If the first digit of a number is found, increase the col and total count.
static void	inc_count(char *str, int *i, int *col, int *total)
{
	if (*i == 0 || str[*i - 1] == ' ' || str[*i - 1] == '-' \
	|| str[*i - 1] == '+' || str[*i - 1] == '\n')
	{
		(*col)++;
		(*total)++;
	}
	(*i)++;
	if (str[*i] == ',')
		skip_colors(str, i);
}

// Some edge case checks at the end of a file.
static void	final_check(int col_max, int col, int *width, int total)
{
	if (total == 0)
		msg_exit("No coordinates\n", false);
	if (col_max == -1)
		*width = col;
}

// Checks if the amount of elements, and the content of the map, are valid.
void	valid_map(char *str, t_data *dat)
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
		if (str[i] == ' ' \
		|| ((str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1])))
			i++;
		else if (ft_isdigit(str[i]))
			inc_count(str, &i, &col, &total);
		else if (str[i] == '\n')
			column_check(&col_max, &col, &dat->width, &i);
		else
			msg_exit("incorrect format\n", false);
	}
	final_check(col_max, col, &dat->width, total);
	if (col != 0)
		column_check(&col_max, &col, &dat->width, &i);
	dat->nodes = total;
}
