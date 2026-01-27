/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:46:50 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/27 19:36:34 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Controlli da fare:
	// Solo caratteri validi: '0', '1', 'N', 'S', 'E', 'W', ' ' (spazio)
	// Esattamente 1 player (N/S/E/W)
	// Estrarre posizione e direzione player
#include "cub3d.h"

int	validate_and_find_player(t_game *game)
{
	int		y;
	int		x;
	int		player_x;
	int		player_y;
	char	player_dir;

	player_x = -1;
	player_y = -1;
	player_dir = '\0';
	// Scorro la mappa
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			// Check validità carattere
			if (!is_valid_map_char(game->map->grid[y][x]))
			{
				fd_printf(2, "Error: Invalid character '%c' in map at position (%d, %d)\n",
					game->map->grid[y][x], x, y);
				return (-1);
			}
			// Check se e' il player
			if (is_player_char(game->map->grid[y][x]))
			{
				// Controllo che non ci sia già un altro player
				if (game->map->player_count > 0)
				{
					fd_printf(2, "Error: Multiple player found in map\n");
					return (-1);
				}
				// Salvo posizione e direzione del player
				player_x = x;
				player_y = y;
				player_dir = game->map->grid[y][x];
				game->map->player_count++;
			}
			x++;
		}
		y++;
	}
	// Controllo che ci sia esattamente un player
	if (game->map->player_count != 1)
	{
		fd_printf(2, "Error: Invalid number of players in map (found %d, expected 1)\n",
			game->map->player_count);
		return (-1);
	}
	// Inizializzo posizione e direzione del player
	init_player_position(game, player_x, player_y, player_dir);
	fd_printf(1, "Player initialized at (%.2f, %.2f) facing '%c'\n",
		game->player->pos_x, game->player->pos_y, game->player->spawn_dir);
	return (0);
}