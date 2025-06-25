/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_circle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:25:56 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/25 12:59:17 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_draw.h"
#include "mlx.h"
#include <stdbool.h>

void	ft_draw_circle(t_mlx *mlx, void *win_ptr, t_circle element)
{
	int	y;
	int	x;

	if (!mlx || !mlx->mlx_ptr || !win_ptr)
		return ;
	y = -element.radius;
	while (y <= element.radius)
	{
		x = -element.radius;
		while (x <= element.radius)
		{
			if (x * x + y * y <= element.radius * element.radius)
				mlx_pixel_put(mlx->mlx_ptr, win_ptr, element.x + x, element.y
					+ y, element.color);
			x++;
		}
		y++;
	}
}
