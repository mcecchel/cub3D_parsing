/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:22:07 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/27 12:46:42 by mcecchel         ###   ########.fr       */
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
		// Se NON è un identificatore valido è l'inizio della mappa
		if (is_valid_identifier(game->parse->file_lines[i]))
		{
			elements_found++;
			i++;
			continue ;
		}
		// Se non è vuota e non è un elemento valido, è l'inizio della mappa
		if (elements_found >= 6)
		{
			game->parse->map_start = i;
			return (0);
		}
		else
		{
			fd_printf(2, "Error: Invalid element at line %d\n", i + 1);
			return (-1);
		}
	}
	// Se arriviamo qui, non abbiamo trovato la mappa
	fd_printf(2, "Error: Map not found in file\n");
	return (-1);
}