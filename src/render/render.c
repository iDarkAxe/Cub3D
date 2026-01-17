/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:13:06 by rdesprez          #+#    #+#             */
/*   Updated: 2026/01/17 11:06:37 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include <math.h>

static int	raycast_column(t_data *data, int x, t_raydata *rdata);

void	cub_render(t_data *data)
{
	t_vec2		plane;
	t_raydata	rdata;
	int			cols_per_thread;

	plane = vec2rotate((t_vec2){0, data->player.fov * 0.5f},
			data->player.angle);
	cols_per_thread = data->mlx.win_size.x / RENDER_THREADS;
	fill_thread_pool(data, plane);
	wait_thread_pool(data);
	rdata.plane = plane;
	rdata.ray_dir.x = cos(data->player.angle);
	rdata.ray_dir.y = sin(data->player.angle);
	cub_render_sprites(data, &rdata);
}

void	cub_render_x_column(t_data *data, int x, const t_vec2 *plane)
{
	t_raydata	rdata;

	rdata.plane = *plane;
	if (!raycast_column(data, x, &rdata))
	{
		data->mlx.z_buffer[x] = 1e30;
		cubmlx_putvertline(data, (t_pos2){x, 0}, data->mlx.win_size.y * 0.5,
			data->map.textures.ceiling.argb);
		cubmlx_putvertline(data, (t_pos2){x, data->mlx.win_size.y * 0.5},
			data->mlx.win_size.y * 0.5, data->map.textures.floor.argb);
		return ;
	}
	draw_column(data, x, &rdata);
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
