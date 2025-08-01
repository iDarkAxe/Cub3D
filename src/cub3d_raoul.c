/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raoul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/08/01 12:04:39 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// Raoul's includes
#include "cub3d.h"
#include "cub3d_render.h"
#include "ft_print.h"
#include <fcntl.h>
#include <stdio.h>

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
