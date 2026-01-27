/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:07:35 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/27 11:18:34 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_rgb_val(int value)
{
	if (value < 0 || value > 255)
	{
		fd_printf(2, "Error: RGB value out of range (must be 0-255)");
		return (-1);
	}
	return (0);
}

int	parse_rgb_values(char *rgb_str, int *values)
{
	char	**rgb_strs;
	int		i;

	rgb_strs = ft_split(rgb_str, ',');
	if (!rgb_strs)
	{
		fd_printf(2, "Error: Memory allocation failed\n");
		return (-1);
	}
	i = 0;
	// Check se in rgb_strs ci sono esattamente 3 valori (r, g, b)
	while (rgb_strs[i])
		i++;
	if (i != 3)
	{
		fd_printf(2, "Error: Invalid RGB format (expected 3 values)\n");
		free_array(rgb_strs);
		return (-1);
	}
	// Converto e valido ogni valore RGB
	i = 0;
	while (i < 3)
	{
		if (!is_valid_nbr(rgb_strs[i]))
		{
			fd_printf(2, "Error: RGB value is not a valid number\n");
			free_array(rgb_strs);
			return (-1);
		}
		// Converto in int
		values[i] = ft_atoi(rgb_strs[i]);
		// Valido range
		if (validate_rgb_val(values[i]) == -1)
		{
			free_array(rgb_strs);
			return (-1);
		}
		i++;
	}
	free_array(rgb_strs);
	return (0);
}

// Formula: 0xRRGGBB = (R << 16) | (G << 8) | B
int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

char	*extract_rgb_str(char *line, int identifier_len)
{
	char	*rgb_str;
	char	*trimmed;
	int		i;

	i = identifier_len;
	i = skip_whitespaces(line, i);
	if (!line[i])
		return (NULL);
	// Estrai la parte RGB
	rgb_str = ft_strdup(&line[i]);
	if (!rgb_str)
		return (NULL);
	// Rimuovi newline, spazi e tab all'inizio e alla fine
	trimmed = ft_strtrim(rgb_str, " \t\n\r");
	free(rgb_str);
	return (trimmed);
}