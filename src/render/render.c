/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:13:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/10/08 15:59:39 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include <math.h>

static int	raycast_column(t_data *data, int x, t_raydata *rdata);
void		cub_render_sprites(t_data *data, t_raydata *rdata);

void	cub_render(t_data *data)
{
	int			x;
	t_raydata	rdata;

	x = 0;
	count_fps(1);
	rdata.plane = vec2rotate((t_vec2){0, data->player.fov * 0.5f},
			data->player.angle);
	while (x < data->mlx.win_size.x)
	{
		if (!raycast_column(data, x, &rdata))
		{
			data->mlx.z_buffer[x] = 1e30;
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
	rdata.ray_dir.x = cos(data->player.angle);
	rdata.ray_dir.y = sin(data->player.angle);
	cub_render_sprites(data, &rdata);
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
