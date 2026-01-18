/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov_zone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:50:26 by ppontet          #+#    #+#             */
/*   Updated: 2026/01/18 20:59:53 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include <math.h>

static void		ray_dir_calc(t_raydata *rdata);
static float	ray_exit_rect(t_pos2 o, float angle, float max_t,
					t_pos2 size);

float	ray_exit_rect(t_pos2 o, float angle, float max_t,
	t_pos2 size)
{
	t_vec2	ray_len;
	float	dx;
	float	dy;

	dx = cosf(angle);
	dy = sinf(angle);
	ray_len = (t_vec2){max_t, max_t};
	if (dx > 0)
		ray_len.x = (size.x - 1 - o.x) / dx;
	else if (dx < 0)
		ray_len.x = -o.x / dx;
	if (dy > 0)
		ray_len.y = (size.y - 1 - o.y) / dy;
	else if (dy < 0)
		ray_len.y = -o.y / dy;
	if (ray_len.x < ray_len.y)
		return (fmin(ray_len.x, max_t));
	return (fmin(ray_len.y, max_t));
}

t_pos2	minimap_ray_endpoint(t_data *data, t_pos2 origin, float angle,
	float dist)
{
	float	travel_dist;

	travel_dist = ray_exit_rect(origin, angle, dist * MINIMAP_TILE_SIZE,
			data->mlx.minimap_size);
	return ((t_pos2){origin.x + cosf(angle) * travel_dist,
		origin.y + sinf(angle) * travel_dist});
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
