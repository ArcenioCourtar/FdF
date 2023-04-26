/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:30:48 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/26 16:59:00 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

/*
	TODO: Norm compliance
	Handling int over/underflow
	more rigorous testing of map validity
*/

static int	valid_args(int argc, char **argv)
{
	char	*str;
	int		fd;

	if (argc != 2)
	{
		ft_printf("Usage: ./FdF map.fdf\n");
		exit(EXIT_SUCCESS);
	}
	if (ft_strlen(argv[1]) < 5)
	{
		ft_printf("Invalid file name\n");
		exit(EXIT_SUCCESS);
	}
	str = argv[1] + (ft_strlen(argv[1]) - 4);
	if (ft_strncmp(str, ".fdf", 4) != 0)
	{
		ft_printf("Invalid file name\n");
		exit(EXIT_SUCCESS);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror(argv[0]);
		exit(EXIT_SUCCESS);
	}
	return (fd);
}

static char	*concat_str(char *old, char buffer[1001])
{
	char	*new;
	int		oldlen;
	int		bufflen;

	oldlen = ft_strlen(old);
	bufflen = ft_strlen(buffer);
	new = malloc(oldlen + bufflen + 1);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, old, oldlen);
	free(old);
	ft_memcpy(new + oldlen, buffer, bufflen);
	new[oldlen + bufflen] = '\0';
	return (new);
}

static char	*read_file(int fd)
{
	char	buffer[1001];
	char	*str;
	int		bytesread;

	str = NULL;
	while (1)
	{
		ft_bzero(buffer, 1001);
		bytesread = read(fd, buffer, 1000);
		if (bytesread <= 0)
			return (str);
		if (str == NULL)
		{
			str = malloc(bytesread + 1);
			if (str == NULL)
				exit(EXIT_FAILURE);
			ft_memcpy(str, buffer, bytesread);
		}		
		else
			str = concat_str(str, buffer);
		if (str == NULL)
			exit(EXIT_FAILURE);
	}
}

static int	valid_map(char *str, int *width)
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
		{
			if (i == 0 || str[i - 1] == ' ' || str[i - 1] == '-' \
			|| str[i - 1] == '+' || str[i - 1] == '\n')
			{
				col++;
				total++;
			}
			i++;
		}
		else if (str[i] == '\n')
		{
			if (col_max == -1)
			{
				col_max = col;
				*width = col_max;
			}
			else if (col_max != col)
			{
				ft_printf("Wrong cols. expect: %i, found: %i\n", col_max, col);
				exit(EXIT_SUCCESS);
			}
			col = 0;
			i++;
		}
		else
		{
			ft_printf("incorrect formatting\n");
			exit(EXIT_FAILURE);
		}
	}
	return (total);
}

/* 
	fdf given by 42Schools:
	Runs without newline after last row.
	Runs if file name does not end in .fdf.
	Runs regardless of the # of spaces in between numbers,
	and spaces at the start or end of rows.
	Numbers with multiple operators (++1, --1, +-1) lead to undefined behaviour
	it does not mark it as an invalid map though.
*/
char	*valid_check(int argc, char **argv, int *nodes, int *width)
{
	int		fd;
	char	*str;

	fd = valid_args(argc, argv);
	str = read_file(fd);
	if (str == NULL)
		exit(EXIT_SUCCESS);
	*nodes = valid_map(str, width);
	return (str);
}
