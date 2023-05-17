/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:30:48 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/10 17:38:01 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

int	valid_map(char *str, int *width); // parsing_2.c

/*
	TODO: Norm compliance
	Handling int over/underflow
	more rigorous testing of map validity
*/
static int	valid_args(int argcfd, char **argv)
{
	char	*str;

	if (argcfd != 2)
		msg_exit("Usage: ./FdF map.fdf\n", false);
	if (ft_strlen(argv[1]) < 5)
		msg_exit("Invalid file name\n", false);
	str = argv[1] + (ft_strlen(argv[1]) - 4);
	if (ft_strncmp(str, ".fdf", 4) != 0)
		msg_exit("Invalid file name\n", false);
	argcfd = open(argv[1], O_RDONLY);
	if (argcfd == -1)
		msg_exit(argv[0], true);
	return (argcfd);
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
	char	buffer[BUFFSIZ + 1];
	char	*str;
	int		bytesread;

	str = NULL;
	while (1)
	{
		ft_bzero(buffer, BUFFSIZ + 1);
		bytesread = read(fd, buffer, BUFFSIZ);
		if (bytesread <= 0)
			return (str);
		if (str == NULL)
		{
			str = malloc(bytesread + 1);
			if (str == NULL)
				exit(EXIT_FAILURE);
			ft_memcpy(str, buffer, bytesread);
			str[bytesread] = '\0';
		}		
		else
			str = concat_str(str, buffer);
		if (str == NULL)
			exit(EXIT_FAILURE);
	}
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
