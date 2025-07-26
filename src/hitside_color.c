/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitside_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:05:26 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/26 15:41:35 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"

// RED for now
#define HITSIDE_COLOR_NORTH 0xffff0000
// YELLOW for now
#define HITSIDE_COLOR_SOUTH 0xffffff00
// Green for now
#define HITSIDE_COLOR_WEST 0xff00ff00
// Blue for now
#define HITSIDE_COLOR_EAST 0xff0000ff

void	hitside_color(int hitside, const t_pos2 *step, int *color)
{
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
