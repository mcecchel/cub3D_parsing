/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:57:50 by mcecchel          #+#    #+#             */
/*   Updated: 2026/01/23 15:23:01 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*initialize_texture(void)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->path = NULL;
	texture->img = NULL;
	return (texture);
}

t_color	*initialize_color(void)
{
	t_color	*color;

	color = malloc(sizeof(t_color));
	if (!color)
		return (NULL);
	color->red = -1;
	color->green = -1;
	color->blue = -1;
	color->hex = -1;
	return (color);
}

t_map	*initialize_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->player_count = 0;
	return (map);
}

t_player	*initialize_player(void)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->spawn_dir = '\0';
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	return (player);
}

t_parse	*initialize_parse(void)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (NULL);
	parse->file_lines = NULL;
	parse->line_count = 0;
	parse->map_start = -1;
	parse->is_north_set = false;
	parse->is_south_set = false;
	parse->is_west_set = false;
	parse->is_east_set = false;
	parse->is_floor_set = false;
	parse->is_ceiling_set = false;
	return (parse);
}
