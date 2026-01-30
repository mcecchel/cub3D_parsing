/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:55:00 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/29 18:56:43 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_file_lines(char *filename)
{
	int		fd;
	int		line_count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		fd_printf(2, "Error: Could not open file %s\n", filename);
		close(fd);
		return (-1);
	}
	line_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (line_count);
}

int	open_and_read_lines(char *filename, char **total_lines)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		fd_printf(2, "Error: Could not open file %s\n", filename);
		free(total_lines);
		return (-1);
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		total_lines[i] = line;
		i++;
		line = get_next_line(fd);
	}
	total_lines[i] = NULL;
	close(fd);
	return (0);
}
