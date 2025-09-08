/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:50:16 by rdesprez          #+#    #+#             */
/*   Updated: 2025/09/08 10:57:51 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"

void	cubmlx_render_minimap_player(t_data *data, int tile_size);

void	cub_render_minimap(t_data *data)
{
	static const int	tile_size = MINIMAP_TILE_SIZE;
	size_t				x;
	size_t				y;
	t_pos2				pos;

	if (!data || !data->map.map)
		return ;
	y = 0;
	while (y < data->map.map->height)
	{
		x = 0;
		pos.y = y * tile_size;
		while (x < data->map.map->width)
		{
			pos.x = x * tile_size;
			if (data->map.map->walls[y * data->map.map->width + x])
				cubmlx_putsquare(data, pos, tile_size, MINIMAP_WALL_COLOR);
			else
				cubmlx_putsquare(data, pos, tile_size, MINIMAP_FLOOR_COLOR);
			x++;
		}
		y++;
	}
	cubmlx_render_minimap_player(data, tile_size);
}
