/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:05:26 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/16 23:40:44 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include <math.h>

static void	raycalc_set_ray_dir(t_raydata *rdata, const t_vec2 *pos);

void	raycalc(int x, float cam_angle, t_vec2 plane, t_raydata *rdata)
{
	float	cam_x;

	cam_x = 2 * x / (float)WINDOW_WIDTH - 1.f;
	rdata->ray_dir.x = cos(cam_angle) + plane.x * cam_x;
	rdata->ray_dir.y = sin(cam_angle) + plane.y * cam_x;
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
		rdata->side_dist.x = (rdata->map.x + 1.f - pos->x) * rdata->delta_dist.x;
	}
	if (rdata->ray_dir.y < 0)
	{
		rdata->step.y = -1;
		rdata->side_dist.y = (pos->y - rdata->map.y) * rdata->delta_dist.y;
	}
	else
	{
		rdata->step.y = 1;
		rdata->side_dist.y = (rdata->map.y + 1.f - pos->y) * rdata->delta_dist.y;
	}
}
