/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:40:36 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/29 17:51:25 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_north_texture(t_game *game, char *line)
{
	// Check se ci sono duplicati
	if (game->parse->is_north_set)
	{
		fd_printf(2, "Error: Duplicate north texture\n");
		return (-1);
	}
	// Estraggo path
	game->tex_north->path = get_texture_path(line, 2);
	if (!game->tex_north->path)
		return (-1);
	// Valido file
	if (validate_texture_file(game->tex_north->path) == -1)
		return (-1);
	game->parse->is_north_set = true;
	return (0);
}

int	parse_south_texture(t_game *game, char *line)
{
	if (game->parse->is_south_set)
	{
		fd_printf(2, "Error: Duplicate south texture\n");
		return (-1);
	}
	game->tex_south->path = get_texture_path(line, 2);
	if (!game->tex_south->path)
		return (-1);
	if (validate_texture_file(game->tex_south->path) == -1)
		return (-1);
	game->parse->is_south_set = true;
	return (0);
}

int	parse_west_texture(t_game *game, char *line)
{
	if (game->parse->is_west_set)
	{
		fd_printf(2, "Error: Duplicate west texture\n");
		return (-1);
	}
	game->tex_west->path = get_texture_path(line, 2);
	if (!game->tex_west->path)
		return (-1);
	if (validate_texture_file(game->tex_west->path) == -1)
		return (-1);
	game->parse->is_west_set = true;
	return (0);
}

int	parse_east_texture(t_game *game, char *line)
{
	if (game->parse->is_east_set)
	{
		fd_printf(2, "Error: Duplicate east texture\n");
		return (-1);
	}
	game->tex_east->path = get_texture_path(line, 2);
	if (!game->tex_east->path)
		return (-1);
	if (validate_texture_file(game->tex_east->path) == -1)
		return (-1);
	game->parse->is_east_set = true;
	return (0);
}
