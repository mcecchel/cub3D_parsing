/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:56:36 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/27 20:05:30 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Conta il numero di righe nel file
static int	count_file_lines(char *filename)
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

char	**read_file_lines(char *filename, int *line_count)
{
	int		fd;
	char	**total_lines;
	char	*line;
	int		i;

	// Conto le righe del file
	*line_count = count_file_lines(filename);
	if (*line_count <= 0)
	{
		fd_printf(2, "Error: File %s is empty or cannot be read\n", filename);
		return (NULL);
	}
	// Alloco l'array di stringhe
	total_lines = malloc(sizeof(char *) * (*line_count + 1));
	if (!total_lines)
	{
		fd_printf(2, "Error: Memory allocation failed\n");
		return (NULL);
	}
	// Riapro il file per leggere le righe
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		fd_printf(2, "Error: Could not open file %s\n", filename);
		free(total_lines);
		close(fd);
		return (NULL);
	}
	// Leggo le righe e le salvo nell'array
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		// Rimuovo newline finale se presente
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		total_lines[i] = line;
		i++;
		line = get_next_line(fd);
	}
	total_lines[i] = NULL;
	close(fd);
	return (total_lines);
}

int	load_file_to_parse(t_game *game, char *filename)
{
	if (!game || !game->parse)
		return (-1);
	game->parse->file_lines = read_file_lines(filename,
			&game->parse->line_count);
	if (!game->parse->file_lines)
		return (-1);
	return (0);
}
