/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:30:48 by acourtar          #+#    #+#             */
/*   Updated: 2023/05/24 19:46:15 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42.h"
#include "../include/libft.h"
#include "../include/fdf.h"

int	valid_map(char *str, t_data *dat); // parsing_2.c

// Initial and simple checks for erroneous arguments.
static int	valid_args(int argc, char **argv)
{
	char	*str;

	if (argc != 2 && argc != 3)
		msg_exit("Usage: ./FdF map.fdf [OPTION]\n", false);
	if (ft_strlen(argv[1]) < 5)
		msg_exit("Invalid file name\n", false);
	str = argv[1] + (ft_strlen(argv[1]) - 4);
	if (ft_strncmp(str, ".fdf", 4) != 0)
		msg_exit("Invalid file name\n", false);
	argc = open(argv[1], O_RDONLY);
	if (argc == -1)
		msg_exit(argv[0], true);
	return (argc);
}

// get_next_line() rethread
static char	*concat_str(char *old, char buffer[BUFFSIZ + 1])
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

// get_next_line() rethread
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
	Runs without newline after last row. (KEPT)
	Runs if file name does not end in .fdf. (CHANGED)
	Runs regardless of the # of spaces in between numbers,
	and spaces at the start or end of rows. (KEPT)
	Numbers with multiple operators (++1, --1, +-1) lead to undefined behaviour
	it does not mark it as an invalid map though. (CHANGED, UB)
*/
void	valid_check(int argc, char **argv, t_data *dat)
{
	int		fd;
	char	*str;

	fd = valid_args(argc, argv);
	str = read_file(fd);
	if (str == NULL)
		msg_exit("empty file.\n", false);
	valid_map(str, dat);
	dat->str = str;
	dat->argc = argc;
	dat->argv = argv;
}
