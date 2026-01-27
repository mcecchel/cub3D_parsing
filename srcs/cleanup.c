/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:30:59 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/23 19:02:12 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_texture(game, game->tex_north);
	free_texture(game, game->tex_south);
	free_texture(game, game->tex_west);
	free_texture(game, game->tex_east);
	// Libero i colori floor e ceiling
	if (game->floor)
		free(game->floor);
	if (game->ceiling)
		free(game->ceiling);
	// Libero la mappa
	free_map(game->map);
	// Libero il player
	if (game->player)
		free(game->player);
	// Libero la struttura di parsing
	free_parse(game->parse);
	// Libero l'immagine schermo
	free_screen(game);
	// Distruggo finestra e libero mlx
	if (game->win && game->mlx_init)
		mlx_destroy_window(game->mlx_init, game->win);
	if (game->mlx_init)
	{
		mlx_destroy_display(game->mlx_init);
		free(game->mlx_init);
	}
	free(game);
}
