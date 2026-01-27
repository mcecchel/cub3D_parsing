/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:09:43 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/27 15:31:09 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_height(t_game *game)
{
	int	height;
	int	i;

	height = 0;
	i = game->parse->map_start;
	while (i < game->parse->line_count)
	{
		// Conta solo righe non vuote
		if (!is_line_empty(game->parse->file_lines[i]))
			height++;
		i++;
	}
	return (height);
}

int	get_map_width(t_game *game)
{
	int	current_width;
	int	max_width;
	int	i;

	max_width = 0;
	i = game->parse->map_start;
	while (i < game->parse->line_count)
	{
		if (!is_line_empty(game->parse->file_lines[i]))
		{
			current_width = ft_strlen(game->parse->file_lines[i]);
			if (current_width > max_width)
				max_width = current_width;
		}
		i++;
	}
	return (max_width);
}

char	*pad_map_line(char *line, int width)
{
	int		line_len;
	char	*padded_line;
	int		i;

	padded_line = ft_calloc(width + 1, sizeof(char));
	if (!padded_line)
		return (NULL);
	line_len = ft_strlen(line);
	i = 0;
	// Copio la riga originale
	while (i < line_len)
	{
		padded_line[i] = line[i];
		i++;
	}
	// Aggiungo padding di spazi fino a matchare width
	while (i < width)
	{
		padded_line[i] = ' ';
		i++;
	}
	return (padded_line);
}

char	**alloc_map_grid(int height)
{
	char	**map_grid;

	map_grid = ft_calloc(height + 1, sizeof(char *));
	if (!map_grid)
	{
		fd_printf(2, "Error: Memory allocation failed for map grid\n");
		return (NULL);
	}
	return (map_grid);
}

void	free_map_rows(char **map_grid, int row_count)
{
	while (row_count > 0)
	{
		free(map_grid[row_count - 1]);
		row_count--;
	}
	free(map_grid);
}
