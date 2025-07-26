/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:50:16 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/26 16:04:26 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include <math.h>

static void	render_square(t_data *data, t_pos2 pos, int size,
	unsigned int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			cubmlx_putpixel(data, pos.x + x, pos.y + y, color);
			x++;
		}
		y++;
	}
}

#if ENABLE_FIELD_OF_VIEW == 1

static void	render_line_of_sight(t_data *data, t_pos2 pos, int tile_size)
{
	t_pos2	line_left;
	t_pos2	line_right;

	line_left.x = 8 * cos(data->player.angle - data->player.fov * 0.5)
		+ data->player.pos.x * tile_size;
	line_left.y = 8 * sin(data->player.angle - data->player.fov * 0.5)
		+ data->player.pos.y * tile_size;
	line_right.x = 8 * cos(data->player.angle + data->player.fov * 0.5)
		+ data->player.pos.x * tile_size;
	line_right.y = 8 * sin(data->player.angle + data->player.fov * 0.5)
		+ data->player.pos.y * tile_size;
	cubmlx_putline(data, pos, line_left, MINIMAP_PLAYER_CONE_OF_SIGHT_COLOR);
	cubmlx_putline(data, pos, line_right, MINIMAP_PLAYER_CONE_OF_SIGHT_COLOR);
}

#else

static void	render_line_of_sight(t_data *data, t_pos2 pos, int tile_size)
{
	t_pos2	len;

	len.x = 8 * cos((double)data->player.angle) + (int)(data->player.pos.x)
		* tile_size;
	len.y = 8 * sin((double)data->player.angle) + (int)(data->player.pos.y)
		* tile_size;
	cubmlx_putline(data, pos, len, MINIMAP_PLAYER_LINE_OF_SIGHT_COLOR);
}

#endif

static void	render_minimap_player(t_data *data, int tile_size)
{
	t_pos2	pos;

	pos.x = data->player.pos.x * tile_size - 2;
	pos.y = data->player.pos.y * tile_size - 2;
	render_square(data, pos, 4, MINIMAP_PLAYER_COLOR);
	pos.x = data->player.pos.x * tile_size;
	pos.y = data->player.pos.y * tile_size;
	render_line_of_sight(data, pos, tile_size);
}

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
				render_square(data, pos, tile_size, MINIMAP_WALL_COLOR);
			else
				render_square(data, pos, tile_size, MINIMAP_FLOOR_COLOR);
			x++;
		}
		y++;
	}
	render_minimap_player(data, tile_size);
}
