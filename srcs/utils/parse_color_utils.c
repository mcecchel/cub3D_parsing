/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:07:35 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/29 18:17:56 by mcecchel         ###   ########.fr       */
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

char	**validate_and_split_rgb(char *rgb_str)
{
	char	**rgb_strs;
	int		i;

	if (count_commas(rgb_str) != 2)
	{
		fd_printf(2, "Error: Invalid RGB format (must have 2 commas)\n");
		return (NULL);
	}
	rgb_strs = ft_split(rgb_str, ',');
	if (!rgb_strs)
	{
		fd_printf(2, "Error: Memory allocation failed\n");
		return (NULL);
	}
	i = 0;
	while (rgb_strs[i])
		i++;
	if (i != 3)
	{
		fd_printf(2, "Error: Invalid RGB format (expected 3 values)\n");
		free_array(rgb_strs);
		return (NULL);
	}
	return (rgb_strs);
}

int	process_single_rgb_val(char *rgb_str, int *value)
{
	char	*trimmed;

	trimmed = ft_strtrim(rgb_str, " \t\n\r");
	if (!trimmed)
	{
		fd_printf(2, "Error: Memory allocation failed\n");
		return (-1);
	}
	if (!is_valid_nbr(trimmed))
	{
		fd_printf(2, "Error: RGB value is not a valid number\n");
		free(trimmed);
		return (-1);
	}
	*value = ft_atoi(trimmed);
	free(trimmed);
	if (validate_rgb_val(*value) == -1)
		return (-1);
	return (0);
}

int	parse_rgb_vals(char *rgb_str, int *values)
{
	char	**rgb_strs;
	int		i;

	rgb_strs = validate_and_split_rgb(rgb_str);
	if (!rgb_strs)
		return (-1);
	i = 0;
	while (i < 3)
	{
		if (process_single_rgb_val(rgb_strs[i], &values[i]) == -1)
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
