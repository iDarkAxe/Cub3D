/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:50:26 by rdesprez          #+#    #+#             */
/*   Updated: 2025/09/08 10:57:42 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include <math.h>

static void	render_field_of_view(t_data *data, t_pos2 pos, int tile_size)
{
	static const double	len_line = MINIMAP_PLAYER_SIZE
		* MINIMAP_LINE_OF_SIGHT_FACTOR;
	t_pos2				line_left;
	t_pos2				line_right;

	line_left.x = len_line * cos(data->player.angle - data->player.fov * 0.5)
		+ data->player.pos.x * tile_size;
	line_left.y = len_line * sin(data->player.angle - data->player.fov * 0.5)
		+ data->player.pos.y * tile_size;
	line_right.x = len_line * cos(data->player.angle + data->player.fov * 0.5)
		+ data->player.pos.x * tile_size;
	line_right.y = len_line * sin(data->player.angle + data->player.fov * 0.5)
		+ data->player.pos.y * tile_size;
	cubmlx_putline(data, pos, line_left, MINIMAP_PLAYER_CONE_OF_SIGHT_COLOR);
	cubmlx_putline(data, pos, line_right, MINIMAP_PLAYER_CONE_OF_SIGHT_COLOR);
}

static void	render_line_of_sight(t_data *data, t_pos2 pos, int tile_size)
{
	static const double	len_line = MINIMAP_PLAYER_SIZE
		* MINIMAP_LINE_OF_SIGHT_FACTOR;
	t_pos2				len;

	len.x = len_line * cos(data->player.angle) + (data->player.pos.x)
		* tile_size;
	len.y = len_line * sin(data->player.angle) + (data->player.pos.y)
		* tile_size;
	cubmlx_putline(data, pos, len, MINIMAP_PLAYER_LINE_OF_SIGHT_COLOR);
}

void	cubmlx_render_minimap_player(t_data *data, int tile_size)
{
	static const int	half_player_size = MINIMAP_PLAYER_SIZE * 0.5f;
	t_pos2				pos;

	pos.x = data->player.pos.x * tile_size - half_player_size;
	pos.y = data->player.pos.y * tile_size - half_player_size;
	cubmlx_putsquare(data, pos, MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_COLOR);
	pos.x = data->player.pos.x * tile_size;
	pos.y = data->player.pos.y * tile_size;
	if (data->input.fov)
		render_field_of_view(data, pos, tile_size);
	else
		render_line_of_sight(data, pos, tile_size);
}
