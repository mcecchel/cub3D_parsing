/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:00:37 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/29 18:47:27 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Parsa un singolo elemento (che sia texture o colore)
static int	parse_element(t_game *game, char *line)
{
	int	i;

	i = skip_spaces(line, 0);
	// Controllo se è una texture (NO, SO, WE, EA)
	if (ft_strncmp(&line[i], "NO ", 3) == 0
		|| ft_strncmp(&line[i], "SO ", 3) == 0
		|| ft_strncmp(&line[i], "WE ", 3) == 0
		|| ft_strncmp(&line[i], "EA ", 3) == 0)
		return (parse_texture(game, line));
	// Controllo se è un colore (F, C)
	if (ft_strncmp(&line[i], "F ", 2) == 0
		|| ft_strncmp(&line[i], "C ", 2) == 0)
		return (parse_color(game, line));
	// Se non e' texture, colore o muro, errore
	if (line[i] && line[i] != '1')
	{
		fd_printf(2, "Error: Invalid element identifier: '%c'\n", line[i]);
		return (-1);
	}
	return (0);
}

// Scorre tutte le righe fino a map_start e parsa texture e colori
static int	parse_elements(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->parse->map_start)
	{
		// Salta righe vuote
		if (is_line_empty(game->parse->file_lines[i]))
		{
			i++;
			continue ;
		}
		// Parsa elemento singolo
		if (parse_element(game, game->parse->file_lines[i]) < 0)
		{
			fd_printf(2, "Error: Failed to parse line %d\n",
				i + 1, game->parse->file_lines[i]);
			return (-1); // Errore nel parsing
		}
		i++;
	}
	return (0);
}

// Verifica se ci sono tutti gli elem prima dell'inizio della mappa
static int	are_all_elements_set(t_game *game)
{
	if (!game->parse->is_north_set)
		return (fd_printf(2, "Error: North texture not set.\n"), -1);
	if (!game->parse->is_south_set)
		return (fd_printf(2, "Error: South texture not set.\n"), -1);
	if (!game->parse->is_west_set)
		return (fd_printf(2, "Error: West texture not set.\n"), -1);
	if (!game->parse->is_east_set)
		return (fd_printf(2, "Error: East texture not set.\n"), -1);
	if (!game->parse->is_floor_set)
		return (fd_printf(2, "Error: Floor color not set.\n"), -1);
	if (!game->parse->is_ceiling_set)
		return (fd_printf(2, "Error: Ceiling color not set.\n"), -1);
	return (0);
}

// Funzione principale di parsing
	// filename = Path del file .cub
int	parse_file(t_game *game, char *filename)
{
	if (load_file_to_parse(game, filename) == -1)
		return (-1); // Errore nel caricamento del file
	if (find_map_start(game) == -1)
		return (-1); // Errore nel trovare inizio mappa
	if (parse_elements(game) == -1)
		return (-1); // Errore nel parsing degli elementi
	if (are_all_elements_set(game) == -1)
		return (-1); // Mancano elementi obbligatori
	if (extract_map(game) == -1)
		return (-1); // Errore nell'estrazione della mappa
	fd_printf(1, "✅ Elements parsed successfully!\n");
	fd_printf(1, "North: %s\n", game->tex_north->path);
	fd_printf(1, "South: %s\n", game->tex_south->path);
	fd_printf(1, "West: %s\n", game->tex_west->path);
	fd_printf(1, "East: %s\n", game->tex_east->path);
	fd_printf(1, "Floor: RGB(%d,%d,%d) = 0x%06X\n", game->floor->red,
		game->floor->green, game->floor->blue, game->floor->hex);
	fd_printf(1, "Ceiling: RGB(%d,%d,%d) = 0x%06X\n", game->ceiling->red,
		game->ceiling->green, game->ceiling->blue, game->ceiling->hex);
	return (0);
}
