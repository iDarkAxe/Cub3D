/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raoul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/08/09 11:51:22 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// Raoul's includes
#include "cub3d.h"
#include "cub3d_render.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "maze.h"
#include "mlx.h"
#include <stdlib.h>

int	generate_maze_if_requested(t_data *data, char *gen)
{
	if (data == NULL || gen == NULL)
		return (0);
	if (cub_generate_dimensions(&data->map.map, gen) == 0)
		return (-1);
	ft_printf("Generating maze...\n");
	if (cub_growing_tree(data->map.map) == 0)
	{
		free(data->map.map->walls);
		return (0);
	}
	ft_printf("Maze generated!\n");
	data->mlx.minimap_size.x = data->map.map->width;
	data->mlx.minimap_size.y = data->map.map->height;
	return (0);
}

int	cub3d_init_render(t_data *data)
{
	if (!data)
		return (print_error(NULL, CUB_INIT_RENDER));
	if (cub_init(data) == 0)
		return (print_error(NULL, CUB_INIT_RENDER));
	data->input = (t_input){0};
	data->input.collision = COLLISION_DEFAULT_VALUE;
	data->input.minimap = MINIMAP_DEFAULT_VALUE;
	data->input.fov = FIELD_OF_VIEW_DEFAULT_VALUE;
	data->player.pos.x = data->map.map->start_pos.x + 0.5f;
	data->player.pos.y = data->map.map->start_pos.y + 0.5f;
	data->player.angle = data->map.map->start_angle;
	data->player.fov = (float)(PI) / 2.0f;
	data->map.textures.ceiling.argb = data->map.textures.ceiling.argb;
	data->map.textures.floor.argb = data->map.textures.floor.argb;
	cub_loop(data);
	return (0);
}
