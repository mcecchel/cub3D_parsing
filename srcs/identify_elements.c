/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:22:07 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/27 20:50:55 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_map_start(t_game *game)
{
	int	i;
	int	elements_found;

	i = 0;
	elements_found = 0;
	while (i < game->parse->line_count)
	{
		// Salto righe vuote
		if (is_line_empty(game->parse->file_lines[i]))
		{
			i++;
			continue ;
		}
		// Se è un identificatore valido, incremento counter
		if (is_valid_identifier(game->parse->file_lines[i]))
		{
			elements_found++;
			i++;
			continue ;
		}
		// Se ho trovato tutti i 6 elementi (NO, SO, WE, EA, F, C)
		// e questa riga non è vuota e non è un identificatore,
		// allora è l'inizio della mappa
		if (elements_found == 6)
		{
			game->parse->map_start = i;
			fd_printf(1, "✅ Map starts at line %d\n", i + 1);
			return (0);
		}
		// Altrimenti c'è un errore: riga non valida prima di avere tutti gli elementi
		fd_printf(2, "Error: Invalid line at %d (found %d/6 elements)\n", 
			i + 1, elements_found);
		fd_printf(2, "Line content: '%s'\n", game->parse->file_lines[i]);
		return (-1);
	}
	// Se arriviamo qui, non abbiamo trovato la mappa o mancano elementi
	if (elements_found < 6)
	{
		fd_printf(2, "Error: Missing elements (found %d/6)\n", elements_found);
		return (-1);
	}
	fd_printf(2, "Error: Map not found in file\n");
	return (-1);
}