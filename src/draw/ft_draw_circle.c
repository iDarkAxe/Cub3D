/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_circle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:25:56 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/25 09:02:10 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_draw.h"
#include "mlx.h"

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

void	ft_draw_all_circle(t_mlx *mlx, void *win_settings_ptr,
			enum e_screen_size num)
{
	int	color;

	if (num == 0)
		color = 0xFFAA00;
	else
		color = 0x00FF00;
	if (num == 0 || num == 1)
		ft_draw_circle(mlx, win_settings_ptr, (t_circle){35, 140, 20, color});
	if (num == 0 || num == 2)
		ft_draw_circle(mlx, win_settings_ptr, (t_circle){35, 210, 20, color});
	if (num == 0 || num == 3)
		ft_draw_circle(mlx, win_settings_ptr, (t_circle){35, 280, 20, color});
	if (num == 0 || num == 4)
		ft_draw_circle(mlx, win_settings_ptr, (t_circle){35, 360, 20, color});
}
