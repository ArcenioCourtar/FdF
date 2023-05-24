/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_coords_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:38:53 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/24 18:57:50 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

static uint32_t	full_input(const char *str_hex, char *hex_char, int len)
{
	int			i;
	int			j;
	uint32_t	result;

	i = 0;
	result = 0;
	while (i < len)
	{
		j = 0;
		while (str_hex[i] != hex_char[j])
			j++;
		if (j > 15)
			j -= 6;
		result += j * pow(16, 7 - i);
		i++;
	}
	while (i < 8)
	{
		result += 15 * pow(16, 7 - i);
		i++;
	}
	return (result);
}

static uint32_t	half_input(const char *str_hex, char *hex_char, int len)
{
	int			i;
	int			j;
	uint32_t	result;

	i = 0;
	result = 0;
	while (i < len)
	{
		j = 0;
		while (str_hex[i] != hex_char[j])
			j++;
		if (j > 15)
			j -= 6;
		result += j * pow(16, len - i + 2);
		i++;
	}
	while (i < 6)
	{
		result += 0 * pow(16, i + 2);
		i++;
	}
	result += 15 * pow(16, 1);
	result += 15 * pow(16, 0);
	return (result);
}

static void	convert_hex(t_coords *new, char *str_hex, char *hex_char, int len)
{
	if (len > 5)
		new->color = full_input(str_hex, hex_char, len);
	else
		new->color = half_input(str_hex, hex_char, len);
}

static bool	valid_hex(t_coords *new, const char *str, int len)
{
	static char	*hex_char = "0123456789ABCDEFabcdef";
	char		str_hex[9];
	int			i;

	if (len > 8 || len == 0)
		return (false);
	ft_memcpy(str_hex, str, len);
	str_hex[len] = '\0';
	i = 0;
	while (i < len)
	{
		if (ft_strchr(hex_char, str_hex[i]) == NULL)
			return (false);
		i++;
	}
	convert_hex(new, str_hex, hex_char, len);
	return (true);
}

void	assign_col(t_data *dat, t_coords *new, int *s)
{
	int	start;

	if (dat->str[*s] != ',')
	{
		new->color = COL_WHT;
		(*s)++;
	}
	else
	{
		start = *s + 1;
		while (dat->str[*s] != ' ' && dat->str[*s] != '\0' \
		&& dat->str[*s] != '\n')
			(*s)++;
		if (!(dat->argc == 3 && ft_strncmp(dat->argv[2], "HEIGHT", 6) == 0))
		{
			if (ft_strncmp(&dat->str[start], "0x", 2) == 0)
			{
				if (!valid_hex(new, &dat->str[start + 2], *s - start - 2))
					new->color = COL_WHT;
			}
			else
				new->color = COL_WHT;
		}
	}
}
