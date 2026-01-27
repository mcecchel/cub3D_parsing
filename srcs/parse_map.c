/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:31:48 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/27 20:04:26 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Validazione completa della mappa
int	parse_map(t_game *game)
{
	fd_printf(1, "🔍 Validating map...\n");
	// Valido caratteri e cerco player
	if (validate_and_find_player(game) == -1)
		return (-1);
	// Valido bordi mappa
	if (parse_map_borders(game) == -1)
		return (-1);
	fd_printf(1, "✅ Map validation successful!\n");
	return (0);
}