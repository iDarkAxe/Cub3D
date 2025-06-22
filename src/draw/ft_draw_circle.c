/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_circle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:25:56 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/22 18:26:22 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_draw.h"
#include "mlx.h"

void	ft_draw_circle(void *mlx_ptr, void *win_ptr, t_circle element)
{
	int	y;
	int	x;

	y = -element.radius;
	while (y <= element.radius)
	{
		x = -element.radius;
		while (x <= element.radius)
		{
			if (x * x + y * y <= element.radius * element.radius)
				mlx_pixel_put(mlx_ptr, win_ptr, element.x + x, element.y + y,
					element.color);
			x++;
		}
		y++;
	}
}

void	ft_draw_all_circle(void *mlx_ptr, void *win_settings_ptr, int num)
{
	int	color;

	if (num == 0)
		color = 0xFFAA00;
	else
		color = 0x00FF00;
	if (num == 0 || num == 1)
		ft_draw_circle(mlx_ptr, win_settings_ptr, (t_circle){35, 140, 20,
			color});
	if (num == 0 || num == 2)
		ft_draw_circle(mlx_ptr, win_settings_ptr, (t_circle){35, 210, 20,
			color});
	if (num == 0 || num == 3)
		ft_draw_circle(mlx_ptr, win_settings_ptr, (t_circle){35, 280, 20,
			color});
	if (num == 0 || num == 4)
		ft_draw_circle(mlx_ptr, win_settings_ptr, (t_circle){35, 360, 20,
			color});
}
