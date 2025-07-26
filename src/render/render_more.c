/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:47:02 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/26 15:41:38 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"
#include <math.h>

void		raycalc(const t_pos2 win_size, int x, float cam_angle,
				t_raydata *rdata);
static void	raycalc_set_ray_dir(t_raydata *rdata, const t_vec2 *pos);

// TODO: What is 1e30 magic number ? Maybe define a const or macro
void	raycalc(const t_pos2 win_size, int x, float cam_angle, t_raydata *rdata)
{
	float	cam_x;

	cam_x = 2 * x / (float)win_size.x - 1.f;
	rdata->ray_dir.x = cos(cam_angle) + rdata->plane.x * cam_x;
	rdata->ray_dir.y = sin(cam_angle) + rdata->plane.y * cam_x;
	if (rdata->ray_dir.x == 0.f)
		rdata->delta_dist.x = 1e30;
	else
		rdata->delta_dist.x = absf(1.f / rdata->ray_dir.x);
	if (rdata->ray_dir.y == 0.f)
		rdata->delta_dist.y = 1e30;
	else
		rdata->delta_dist.y = absf(1.f / rdata->ray_dir.y);
	raycalc_set_ray_dir(rdata, &rdata->pos);
}

void	raycalc_set_ray_dir(t_raydata *rdata, const t_vec2 *pos)
{
	if (rdata->ray_dir.x < 0)
	{
		rdata->step.x = -1;
		rdata->side_dist.x = (pos->x - rdata->map.x) * rdata->delta_dist.x;
	}
	else
	{
		rdata->step.x = 1;
		rdata->side_dist.x = (rdata->map.x + 1.f - pos->x)
			* rdata->delta_dist.x;
	}
	if (rdata->ray_dir.y < 0)
	{
		rdata->step.y = -1;
		rdata->side_dist.y = (pos->y - rdata->map.y) * rdata->delta_dist.y;
	}
	else
	{
		rdata->step.y = 1;
		rdata->side_dist.y = (rdata->map.y + 1.f - pos->y)
			* rdata->delta_dist.y;
	}
}
