/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitside_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:05:26 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/26 16:08:04 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"

// TODO: Needs to be adapted to use the color of the pixel of the texture
/**
 * @brief Function to set the color based on the hit side and step direction.
 * 
 * @param hitside
 * @param step 
 * @param color 
 */
void	hitside_color(int hitside, const t_pos2 *step, int *color)
{
	if (!color || !step)
		return ;
	if (hitside)
	{
		if (step->y < 0)
			*color = HITSIDE_COLOR_NORTH;
		else
			*color = HITSIDE_COLOR_SOUTH;
	}
	else
	{
		if (step->x < 0)
			*color = HITSIDE_COLOR_WEST;
		else
			*color = HITSIDE_COLOR_EAST;
	}
}
