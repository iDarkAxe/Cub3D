/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:05:26 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/16 13:34:48 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include <math.h>

void raycalc(int x, float cam_angle, t_vec2 plane, t_vec2 *side_dist,
			 t_vec2 *delta_dis, t_pos2 *map, t_pos2 *step,  const t_vec2 *pos)
{
	t_vec2			ray_dir;
	float			cam_x;
	
	cam_x = 2 * x / (float)WINDOW_WIDTH - 1.f;

	ray_dir.x = cos(cam_angle) + plane.x * cam_x;
	ray_dir.y = sin(cam_angle) + plane.y * cam_x;
	if (ray_dir.x == 0.f)
		delta_dis->x = 1e30;
	else
		delta_dis->x = absf(1.f / ray_dir.x);
	if (ray_dir.y == 0.f)
		delta_dis->y = 1e30;
	else
		delta_dis->y = absf(1.f / ray_dir.y);
	if (ray_dir.x < 0)
	{
		step->x = -1;
		side_dist->x = (pos->x - map->x) * delta_dis->x;
	}
	else
	{
		step->x = 1;
		side_dist->x = (map->x + 1.f - pos->x) * delta_dis->x;
	}
	if (ray_dir.y < 0)
	{
		step->y = -1;
		side_dist->y = (pos->y - map->y) * delta_dis->y;
	}
	else
	{
		step->y = 1;
		side_dist->y = (map->y + 1.f - pos->y) * delta_dis->y;
	}

}

/* 
ray_dir.x = cos(cub->player.angle) + plane.x * cam_x;
ray_dir.y = sin(cub->player.angle) + plane.y * cam_x;
if (ray_dir.x == 0.f)
	delta_dist.x = 1e30;
else
	delta_dist.x = absf(1.f / ray_dir.x);
if (ray_dir.y == 0.f)
	delta_dist.y = 1e30;
else
	delta_dist.y = absf(1.f / ray_dir.y);
if (ray_dir.x < 0)
{
	step.x = -1;
	side_dist.x = (pos.x - map.x) * delta_dist.x;
}
else
{
	step.x = 1;
	side_dist.x = (map.x + 1.f - pos.x) * delta_dist.x;
}
if (ray_dir.y < 0)
{
	step.y = -1;
	side_dist.y = (pos.y - map.y) * delta_dist.y;
}
else
{
	step.y = 1;
	side_dist.y = (map.y + 1.f - pos.y) * delta_dist.y;
} 
	*/
