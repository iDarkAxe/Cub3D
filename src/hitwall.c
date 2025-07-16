/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitwall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:05:26 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/16 14:49:08 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"

void	hitwall_loop(int *hit_wall, t_pos2 *map, t_vec2 *side_dist,
		t_vec2 *delta_dist, t_pos2 *step, const t_cub *cub, int *hit_side)
{
	while (!(*hit_wall))
	{
		if (side_dist->x < side_dist->y)
		{
			side_dist->x += delta_dist->x;
			map->x += step->x;
			*hit_side = 0;
		}
		else
		{
			side_dist->y += delta_dist->y;
			map->y += step->y;
			*hit_side = 1;
		}
		if (map->x < 0 || map->y < 0 || map->x >= (int)cub->map->width
			|| map->y >= (int)cub->map->height)
			break ;
		if (cub->map->walls[map->y * cub->map->width + map->x] > 0)
			*hit_wall = 1;
	}
}
