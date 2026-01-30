/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:02:43 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/28 19:31:08 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	skip_spaces(char *str, int index)
{
	while (str[index] && (str[index] == ' ' || str[index] == '\t'))
		index++;
	return (index);
}

int	is_valid_identifier(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = skip_spaces(line, 0);
	// Controllo gli identificatori a 2 caratteri (NO, SO, WE, EA)
	if (ft_strncmp(&line[i], "NO ", 3) == 0
		|| ft_strncmp(&line[i], "SO ", 3) == 0
		|| ft_strncmp(&line[i], "WE ", 3) == 0
		|| ft_strncmp(&line[i], "EA ", 3) == 0)
		return (1);
	// Controllo gli identificatori a 1 carattere (Floor e Ceiling)
	if (ft_strncmp(&line[i], "F ", 2) == 0
		|| ft_strncmp(&line[i], "C ", 2) == 0)
		return (1);
	return (0);
}

int	is_valid_nbr(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	count_commas(char *str)
{
	int	count;
	int	i;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}
