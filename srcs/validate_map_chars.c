/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:46:50 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/29 19:31:53 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Controlli da fare:
	// Solo caratteri validi: '0', '1', 'N', 'S', 'E', 'W', ' ' (spazio)
	// Esattamente 1 player (N/S/E/W)
	// Estrarre posizione e direzione player
#include "cub3d.h"

void	init_player_position(t_game *game, int x, int y, char dir)
{
	// Posiziono il player al centro della cella
	game->player->pos_x = x + 0.5;
	game->player->pos_y = y + 0.5;
	// Imposto la direzione
	set_player_direction(game->player, dir);
	// Sostituisco il carattere del player con '0' nella mappa
	game->map->grid[y][x] = '0';
}

static int	validate_char_and_check_player(t_game *game, int x, int y)
{
	// Check validità carattere
	if (!is_valid_map_char(game->map->grid[y][x]))
	{
		fd_printf(2, "Error: Invalid character '%c' in map at position"
			"(%d, %d)\n", game->map->grid[y][x], x, y);
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
		game->map->player_count++;
	}
	return (0);
}

static int	scan_map_for_player(t_game *game, int *px, int *py, char *dir)
{
	int	y;
	int	x;

	// Scorro la mappa
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (validate_char_and_check_player(game, x, y) == -1)
				return (-1);
			// Salvo posizione e direzione del player
			if (is_player_char(game->map->grid[y][x]))
			{
				*px = x;
				*py = y;
				*dir = game->map->grid[y][x];
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_and_find_player(t_game *game)
{
	int		player_x;
	int		player_y;
	char	player_dir;

	if (scan_map_for_player(game, &player_x, &player_y, &player_dir) == -1)
		return (-1);
	// Controllo che ci sia esattamente un player
	if (game->map->player_count != 1)
	{
		fd_printf(2, "Error: Invalid number of players in map"
			"(found %d, expected 1)\n", game->map->player_count);
		return (-1);
	}
	// Inizializzo posizione e direzione del player
	init_player_position(game, player_x, player_y, player_dir);
	fd_printf(1, "Player initialized at (%.2f, %.2f) facing '%c'\n",
		game->player->pos_x, game->player->pos_y, game->player->spawn_dir);
	return (0);
}
