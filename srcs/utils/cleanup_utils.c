/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:35:09 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/29 17:59:44 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_texture(t_game *game, t_texture *texture)
{
	if (!texture)
		return ;
	if (texture->path)
		free(texture->path);
	// Libero l'immagine MLX se caricata
	if (texture->img)
	{
		if (texture->img->img && game->mlx_init)
			mlx_destroy_image(game->mlx_init, texture->img->img);
		free(texture->img);
	}
	free(texture);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	// Libero la griglia (array 2d) della mappa
	if (map->grid)
		free_array(map->grid);
	free(map);
}

void	free_parse(t_parse *parse)
{
	if (!parse)
		return ;
	// Libero tutte le righe del file
	if (parse->file_lines)
		free_array(parse->file_lines);
	free(parse);
}

void	free_screen(t_game *game)
{
	if (!game->screen)
		return ;
	if (game->screen->img && game->mlx_init)
		mlx_destroy_image(game->mlx_init, game->screen->img);
	free(game->screen);
}
