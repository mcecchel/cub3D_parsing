/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:04:20 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/29 18:58:20 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_extension(char *filename)
{
	int		len;
	char	*extention;

	if (!filename)
		return (-1);
	len = ft_strlen(filename);
	if (len < 5)// Perche' deve essere almeno 1 lettera + .cub
	{
		fd_printf(2, "Error: Filename too short\n");
		return (-1);
	}
	extention = filename + (len - 4);// Ptr a dove dovrebbe iniziare .cub
	if (ft_strncmp(extention, ".cub", 4) != 0)
	{
		fd_printf(2, "Error: Invalid file extension, expected .cub\n");
		return (-1);
	}
	return (0);
}

int	check_file_access(char *filename)
{
	int	fd;

	if (!filename)
		return (-1);
	// Provo ad aprire il file in lettura
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		fd_printf(2, "Error: Cannot open file,"
			" check if it exists and is readable\n");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	validate_input(int ac, char **av)
{
	if (ac != 2)
	{
		fd_printf(2, "Error: Invalid number of arguments.\n"
			"Usage: ./cub3D <map.cub>\n");
		return (-1);
	}
	if (check_file_extension(av[1]) == -1)
		return (-1);
	if (check_file_access(av[1]) == -1)
		return (-1);
	return (0);
}
