/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:54:38 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/29 18:48:15 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture_path(char *line, int identifier_len)
{
	int		i;
	int		start;
	int		end;
	char	*path;

	// salto identificatori
	i = skip_spaces(line, 0);
	i += identifier_len;
	// salto spazi dopo identificatore
	i = skip_spaces(line, i);
	start = i;
	// trovo fine del path
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	end = i;
	// Check se il path è valido
	if (end == start)
	{
		fd_printf(2, "Error\nTexture path missing\n");
		return (NULL);
	}
	// Duplico path
	path = ft_substr(line, start, end - start);
	if (!path)
	{
		fd_printf(2, "Error\nMemory allocation failed for texture path\n");
		return (NULL);
	}
	return (path);
}

int	validate_texture_file(char *path)
{
	int	fd;

	if (!path)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		fd_printf(2, "Error: Texture file does not exist or cannot be read\n");
		fd_printf(2, "Path: %s\n", path);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	parse_texture(t_game *game, char *line)
{
	int	i;

	i = skip_spaces(line, 0);
	// Identifico il tipo di texture
	if (ft_strncmp(&line[i], "NO ", 3) == 0)
		return (parse_north_texture(game, line));
	else if (ft_strncmp(&line[i], "SO ", 3) == 0)
		return (parse_south_texture(game, line));
	else if (ft_strncmp(&line[i], "WE ", 3) == 0)
		return (parse_west_texture(game, line));
	else if (ft_strncmp(&line[i], "EA ", 3) == 0)
		return (parse_east_texture(game, line));
	// Non dovremmo mai arrivare qui se is_valid_identifier funziona :(
	// Spero iddio che non lo stampi mai
	fd_printf(2, "Error: Invalid texture identifier\n");
	return (-1);
}
