/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:13:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/26 16:14:32 by ppontet          ###   ########lyon.fr   */
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
 * @param data
 */
void	cub_render(t_data *data)
{
	int			x;
	t_raydata	rdata;

	x = 0;
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
		draw_column(data, x, &rdata);
		x++;
	}
	if (ENABLE_MINIMAP == 1)
		cub_render_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
		data->mlx.backbuffer.img, 0, 0);
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
