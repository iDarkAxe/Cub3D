/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:13:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/08/01 12:29:06 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include "mlx.h"

static int	raycast_column(t_data *data, int x, t_raydata *rdata);

/**
 * @brief Main function to render the game.
 * data->player.fov * 0.5f is used to calculate the plane for the camera
 *
 * @param data data structure
 * @param data data structure
 */
void	cub_render(t_data *data)
{
	int			x;
	t_raydata	rdata;

	x = 0;
	count_fps();
	rdata.plane = vec2rotate((t_vec2){0, data->player.fov * 0.5f},
			data->player.angle);
	while (x < data->mlx.win_size.x)
	{
		if (!raycast_column(data, x, &rdata))
		{
			cubmlx_putvertline(data, (t_pos2){x, 0}, data->mlx.win_size.y * 0.5,
				data->map.textures.ceiling.argb);
			cubmlx_putvertline(data, (t_pos2){x, data->mlx.win_size.y * 0.5},
				data->mlx.win_size.y * 0.5, data->map.textures.floor.argb);
			x++;
			continue ;
		}
		if (data->input.minimap)
			draw_column_with_minimap(data, x, &rdata);
		else
			draw_column(data, x, &rdata);
		x++;
	}
}

static int	raycast_column(t_data *data, int x, t_raydata *rdata)
{
	rdata->pos = data->player.pos;
	rdata->map.x = (int)rdata->pos.x;
	rdata->map.y = (int)rdata->pos.y;
	raycalc(data->mlx.win_size, x, data->player.angle, rdata);
	rdata->hit_wall = 0;
	hitwall_loop(data, rdata);
	return (rdata->hit_wall);
}
