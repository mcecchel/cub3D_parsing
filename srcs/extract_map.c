/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:00:54 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/29 18:40:55 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_empty_line(int found, char **grid, int row, int line_num)
{
	if (found > 0)
	{
		fd_printf(2, "Error: Empty line inside map at line %d\n", line_num);
		free_map_rows(grid, row);
		return (-1);
	}
	return (0);
}

static int	process_map_line(char *line, char **grid, int row, int width)
{
	grid[row] = pad_map_line(line, width);
	if (!grid[row])
	{
		free_map_rows(grid, row);
		fd_printf(2, "Error: Memory allocation failed for map row\n");
		return (-1);
	}
	return (0);
}

static int	fill_map_grid(t_game *game, char **map_grid, int map_width)
{
	int	i;
	int	map_row;
	int	found_map_line;

	i = game->parse->map_start;
	map_row = 0;
	found_map_line = 0;
	while (i < game->parse->line_count)
	{
		if (is_line_empty(game->parse->file_lines[i]))
		{
			if (handle_empty_line(found_map_line, map_grid, map_row,
					i + 1) == -1)
				return (-1);
			i++;
			continue ;
		}
		found_map_line = 1;
		if (process_map_line(game->parse->file_lines[i], map_grid,
				map_row, map_width) == -1)
			return (-1);
		map_row++;
		i++;
	}
	return (0);
}

int	extract_map(t_game *game)
{
	int		map_height;
	int		map_width;
	char	**map_grid;

	map_height = get_map_height(game);
	map_width = get_map_width(game);
	if (map_height == 0 || map_width == 0)
	{
		fd_printf(2, "Error: Map is empty\n");
		return (-1);
	}
	// Alloco la griglia 2D
	map_grid = alloc_map_grid(map_height);
	if (!map_grid)
		return (-1);
	if (fill_map_grid(game, map_grid, map_width) == -1)
		return (-1);
	// Assegno la griglia alla struttura di gioco
	game->map->grid = map_grid;
	game->map->width = map_width;
	game->map->height = map_height;
	fd_printf(1, "Map parsed successfully: width=%d, height=%d\n",
		map_width, map_height);
	return (0);
}
