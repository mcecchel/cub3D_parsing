/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:22:07 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/29 18:44:23 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_map_found(t_game *game, int line_index)
{
	game->parse->map_start = line_index;
	fd_printf(1, "✅ Map starts at line %d\n", line_index + 1);
	return (0);
}

static int	handle_invalid_line(char *line, int line_num, int elem_found)
{
	fd_printf(2, "Error: Invalid line at %d (found %d/6 elements)\n",
		line_num, elem_found);
	fd_printf(2, "Line content: '%s'\n", line);
	return (-1);
}

static int	handle_end_errors(int elem_found)
{
	if (elem_found < 6)
	{
		fd_printf(2, "Error: Missing elements (found %d/6)\n", elem_found);
		return (-1);
	}
	fd_printf(2, "Error: Map not found in file\n");
	return (-1);
}

int	find_map_start(t_game *game)
{
	int	i;
	int	elem_found;

	i = 0;
	elem_found = 0;
	while (i < game->parse->line_count)
	{
		if (is_line_empty(game->parse->file_lines[i]))
		{
			i++;
			continue ;
		}
		if (elem_found == 6)
			return (handle_map_found(game, i));
		if (is_valid_identifier(game->parse->file_lines[i]))
		{
			elem_found++;
			i++;
			continue ;
		}
		return (handle_invalid_line(game->parse->file_lines[i],
				i + 1, elem_found));
	}
	return (handle_end_errors(elem_found));
}
