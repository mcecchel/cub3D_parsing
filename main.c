/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:33:54 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/27 20:02:54 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (validate_input(ac, av) == -1)
		exit (-1);
	game = init_structs();
	if (!game)
	{
		fd_printf(2, "Error: Failed to initialize game\n");
		exit (-1);
	}
	// Parsing texture e colori
	if (parse_file(game, av[1]) == -1)
	{
		free_game(game);
		return (1);
	}
	// Estrazione e validazione mappa
	if (parse_map(game) == -1)
	{
		free_game(game);
		return (1);
	}
	// TODO: Inizializzare MLX e game loop
	fd_printf(1, "✅ Game initialized successfully!\n");
	free_game(game);
	return (0);
}
