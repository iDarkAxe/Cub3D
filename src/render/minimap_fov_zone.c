/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov_zone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:50:26 by rdesprez          #+#    #+#             */
/*   Updated: 2026/01/16 19:10:25 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include <math.h>

static void	ray_dir_calc(t_raydata *rdata);

t_pos2	minimap_ray_endpoint(t_data *data, t_pos2 origin, float angle,
	float dist)
{
	t_pos2	end;

	end.x = origin.x + cosf(angle) * dist * MINIMAP_TILE_SIZE;
	if (end.x < 0)
		end.x = 0;
	else if (end.x >= data->mlx.minimap_size.x)
		end.x = data->mlx.minimap_size.x - 1;
	end.y = origin.y + sinf(angle) * dist * MINIMAP_TILE_SIZE;
	if (end.y < 0)
		end.y = 0;
	else if (end.y >= data->mlx.minimap_size.y)
		end.y = data->mlx.minimap_size.y - 1;
	return (end);
}

float	minimap_raycast(t_data *data, float ray_angle)
{
	t_raydata	rdata;

	rdata = (t_raydata){.pos = data->player.pos, .map = {data->player.pos.x,
		data->player.pos.y}, .ray_dir = {cosf(ray_angle), sinf(ray_angle)},
		.hit_wall = 0};
	rdata.delta_dist.x = absf(1.f / rdata.ray_dir.x);
	rdata.delta_dist.y = absf(1.f / rdata.ray_dir.y);
	ray_dir_calc(&rdata);
	hitwall_loop(data, &rdata);
	if (!rdata.hit_wall)
		return (0.f);
	if (rdata.hit_side == 0)
		return (rdata.side_dist.x - rdata.delta_dist.x);
	return (rdata.side_dist.y - rdata.delta_dist.y);
}

void	ray_dir_calc(t_raydata *rdata)
{
	if (rdata->ray_dir.x < 0)
	{
		rdata->step.x = -1;
		rdata->side_dist.x = (rdata->pos.x - rdata->map.x)
			* rdata->delta_dist.x;
	}
	else
	{
		rdata->step.x = 1;
		rdata->side_dist.x = (rdata->map.x + 1.0f - rdata->pos.x)
			* rdata->delta_dist.x;
	}
	if (rdata->ray_dir.y < 0)
	{
		rdata->step.y = -1;
		rdata->side_dist.y = (rdata->pos.y - rdata->map.y)
			* rdata->delta_dist.y;
	}
	else
	{
		rdata->step.y = 1;
		rdata->side_dist.y = (rdata->map.y + 1.0f - rdata->pos.y)
			* rdata->delta_dist.y;
	}
}
