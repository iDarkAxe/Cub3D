/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitwall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:05:26 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/26 15:41:35 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"

void	hitwall_loop(const t_data *data, t_raydata *rdata)
{
	while (!(rdata->hit_wall))
	{
		if (rdata->side_dist.x < rdata->side_dist.y)
		{
			rdata->side_dist.x += rdata->delta_dist.x;
			rdata->map.x += rdata->step.x;
			rdata->hit_side = 0;
		}
		else
		{
			rdata->side_dist.y += rdata->delta_dist.y;
			rdata->map.y += rdata->step.y;
			rdata->hit_side = 1;
		}
		if (rdata->map.x < 0 || rdata->map.y < 0
			|| rdata->map.x >= (int)data->map.map->width
			|| rdata->map.y >= (int)data->map.map->height)
			break ;
		if (data->map.map->walls[rdata->map.y * data->map.map->width + rdata->map.x] > 0)
			rdata->hit_wall = 1;
	}
}
