/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:58:30 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/27 19:41:15 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
// NB: momentaneamente inizialzzo tutto a NULL/0

t_game	*init_structs(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx_init = NULL;
	game->win = NULL;
	game->screen = NULL;
	game->tex_north = initialize_texture();
	game->tex_south = initialize_texture();
	game->tex_west = initialize_texture();
	game->tex_east = initialize_texture();
	game->floor = initialize_color();
	game->ceiling = initialize_color();
	game->map = initialize_map();
	game->player = initialize_player();
	game->parse = initialize_parse();
	if (!game->tex_north || !game->tex_south || !game->tex_west
		|| !game->tex_east || !game->floor || !game->ceiling
		|| !game->map || !game->player || !game->parse)
	{
		free_game(game);
		return (NULL);
	}
	return (game);
}
