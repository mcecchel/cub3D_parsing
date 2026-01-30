/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_borders.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:27:41 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/29 19:29:49 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Forward declaration, Flood fill ricorsivo per controllare i bordi
static int	flood_fill(t_game *game, char **map_copy, int x, int y);

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

static int	flood_fill(t_game *game, char **map_copy, int x, int y)
{
	// Controllo se la posizione e' fuori dai limiti 
	if (!is_valid_position(game, x, y))
	{
		fd_printf(2, "Error: Map is not closed at position (%d, %d)\n", x, y);
		return (-1);
	}
	// Se e' una parete o un punto gia' visitato, ritorno
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'V')
		return (0);
	// Controllo se c'e' spazio vuoto - uno spazio raggiungibile è un errore
	if (map_copy[y][x] == ' ')
	{
		fd_printf(2, "Error: Map is not closed, reachable space at"
			" (%d, %d)\n", x, y);
		return (-1);
	}
	// Check se carattere non valido, dato che e' gia' gestito ritorna solo 0
	if (map_copy[y][x] != '0')
		return (0);
	// Marco la cella come visitata
	map_copy[y][x] = 'V';
	// Chiamo ricorsivamente per le 4 direzioni
	return (flood_fill_recursive(game, map_copy, x, y));
}
int	check_borders_are_walls(t_game *game)
{
	if (check_top_bottom_borders(game) == -1)
		return (-1);
	if (check_left_right_borders(game) == -1)
		return (-1);
	return (0);
}

int	validate_map_borders(t_game *game)
{
	char	**map_copy;
	int		player_x;
	int		player_y;
	int		result;

	// Prima controllo che i bordi esterni siano tutti muri o spazi
	if (check_borders_are_walls(game) == -1)
		return (-1);
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
