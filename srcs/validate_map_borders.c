/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_borders.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:27:41 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/27 20:43:28 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Forward declaration
static int	flood_fill(t_game *game, char **map_copy, int x, int y);

// Crea una copia della mappa
static char	**copy_map(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = ft_calloc(game->map->height + 1, sizeof(char *));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < game->map->height)
	{
		map_copy[i] = ft_strdup(game->map->grid[i]);
		if (!map_copy[i])
		{
			while (i > 0)
			{
				free(map_copy[i - 1]);
				i--;
			}
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	return (map_copy);
}

// Controlla se una posizione è valida
static bool	is_valid_position(t_game *game, int x, int y)
{
	if (x < 0 || y < 0)
		return (false);
	if (x >= game->map->width || y >= game->map->height)
		return (false);
	// if (game->map->grid[y][x] == ' ')
	// 	return (false);
	return (true);
}
static int	flood_fill_recursive(t_game *game, char **map_copy, int x, int y)
{
	if (flood_fill(game, map_copy, x + 1, y) == -1)
		return (-1);
	if (flood_fill(game, map_copy, x - 1, y) == -1)
		return (-1);
	if (flood_fill(game, map_copy, x, y + 1) == -1)
		return (-1);
	if (flood_fill(game, map_copy, x, y - 1) == -1)
		return (-1);
	return (0);
}

// Flood fill ricorsivo per controllare i bordi
static int	flood_fill(t_game *game, char **map_copy, int x, int y)
{
	// Controllo se la posizione e' fuori dai limiti 
	if (!is_valid_position(game, x, y))
	{
		fd_printf(2, "Error: Map is not closed at position (%d, %d)\n", x, y);
		return (-1);
	}
	// Controllo se c'e' spazio vuoto sui bordi
	if (map_copy[y][x] == ' ')
	{
		// Se siamo sul bordo e c'è uno spazio, la mappa non e'chiusa
		if (x == 0 || y == 0 || x == game->map->width - 1 
				|| y == game->map->height - 1)
		{
			fd_printf(2, "Error: Map is not closed, space on border\n");
			return (-1);
		}
		return (0);
	}
	// Se e' una parete o un punto gia' visitato, ritorno
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'V')
		return (0);
	// Check se carattere non valido, dato che e' gia' gestito ritorna solo 0
	if (map_copy[y][x] != '0')
		return (0);
	// Marco la cella come visitata
	map_copy[y][x] = 'V';
	// Chiamo ricorsivamente per le 4 direzioni
	return (flood_fill_recursive(game, map_copy, x, y));
}

int	validate_map_borders(t_game *game)
{
	char	**map_copy;
	int		player_x;
	int		player_y;
	int		result;

	// Creo una copia della mappa
	map_copy = copy_map(game);
	if (!map_copy)
	{
		fd_printf(2, "Error: Memory allocation failed for map copy\n");
		return (-1);
	}
	// Ottengo posiz player convertendo da double a int
	player_x = (int)(game->player->pos_x);
	player_y = (int)(game->player->pos_y);
	// Faccio flood fill
	result = flood_fill(game, map_copy, player_x, player_y);
	// Libero la copia della mappa
	free_array(map_copy);
	if (result == 0)
		fd_printf(1, "Map borders are valid and closed\n");
	return (result);
}