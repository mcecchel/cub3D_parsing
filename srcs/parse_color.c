/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:07:11 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/27 11:47:06 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	debug_color_parsing(char *line)
{
	fd_printf(2, "DEBUG - Line: [%s]\n", line);
	fd_printf(2, "DEBUG - Line length: %d\n", ft_strlen(line));
	int i = 0;
	while (line[i])
	{
		fd_printf(2, "DEBUG - Char[%d]: '%c'\n", i, line[i], line[i]);
		i++;
	}
}

int	parse_floor_color(t_game *game, char *line)
{
	char	*rgb_str;
	int		rgb_val[3];

	// Controllo se ci sono duplicati
	if (game->parse->is_floor_set)
	{
		fd_printf(2, "Error: Floor color already set\n");
		return (-1);
	}
	// Estraggo riga RGB dopo F
	rgb_str = extract_rgb_str(line, 1);
	if (!rgb_str)
	return (-1);
	debug_color_parsing(rgb_str);
	// Parso e valido i valori RGB
	if (parse_rgb_values(rgb_str, rgb_val) == -1)
	{
		free(rgb_str);
		return (-1);
	}
	free(rgb_str);
	// Creo struttura colore e salvo in game
	game->floor->red = rgb_val[0];
	game->floor->green = rgb_val[1];
	game->floor->blue = rgb_val[2];
	game->floor->hex = rgb_to_hex(rgb_val[0], rgb_val[1], rgb_val[2]);
	game->parse->is_floor_set = true;
	return (0);
}

// Procedimento come sopra
int	parse_ceiling_color(t_game *game, char *line)
{
	char	*rgb_str;
	int		rgb_val[3];

	if (game->parse->is_ceiling_set)
	{
		fd_printf(2, "Error: Ceiling color already set\n");
		return (-1);
	}
	rgb_str = extract_rgb_str(line, 1);
	if (!rgb_str)
	return (-1);
	debug_color_parsing(rgb_str);
	if (parse_rgb_values(rgb_str, rgb_val) == -1)
	{
		free(rgb_str);
		return (-1);
	}
	free(rgb_str);
	game->ceiling->red = rgb_val[0];
	game->ceiling->green = rgb_val[1];
	game->ceiling->blue = rgb_val[2];
	game->ceiling->hex = rgb_to_hex(rgb_val[0], rgb_val[1], rgb_val[2]);
	game->parse->is_ceiling_set = true;
	return (0);
}

// Main function
int	parse_color(t_game *game, char *line)
{
	int	i;

	i = skip_whitespaces(line, 0);
	// Identifico se è floor o ceiling
	if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (parse_floor_color(game, line));
	else if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (parse_ceiling_color(game, line));
	else
	{
		fd_printf(2, "Error: Invalid color identifier\n");
		return (-1);
	}
}
