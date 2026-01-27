/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:00:54 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/27 14:50:15 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_map_grid(t_game *game, char **map_grid, int map_width)
{
	int	i;
	int	map_row;

	i = game->parse->map_start;
	map_row = 0;
	while (i < game->parse->line_count)
	{
		if (is_line_empty(game->parse->file_lines[i]))
		{
			i++;
			continue ;
		}
		map_grid[map_row] = pad_map_line(game->parse->file_lines[i], map_width);
		if (!map_grid[map_row])
		{
			free_map_rows(map_grid, map_row);
			fd_printf(2, "Error: Memory allocation failed for map row\n");
			return (-1);
		}
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

	// Calcolo dimensioni mappa
	map_height = get_map_height(game);
	map_width = get_map_width(game);
	// Controllo che la mappa non sia vuota
	if (map_height == 0 || map_width == 0)
	{
		fd_printf(2, "Error: Map is empty\n");
		return (-1);
	}
	// Alloco la griglia 2D
	map_grid = alloc_map_grid(map_height);
	if (!map_grid)
		return (-1);
	// Riempio la griglia con le righe della mappa
	if (fill_map_grid(game, map_grid, map_width) == -1)
		return (-1);
	// Assegno la griglia alla struttura di gioco
	game->map->grid = map_grid;
	game->map->width = map_width;
	game->map->height = map_height;
	fd_printf(1, "Map parsed successfully: width=%d, height=%d\n", map_width, map_height);
	return (0);
}
