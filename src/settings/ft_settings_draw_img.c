/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings_draw_img.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 08:48:53 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/20 12:19:02 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_circle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:25:56 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/25 08:48:20 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_draw.h"
#include "mlx.h"
#include <errno.h>

void	ft_put_circle_to_win(t_mlx *mlx, void *win_ptr, t_circle element,
		bool is_enabled)
{
	if (!mlx || !mlx->mlx_ptr || !win_ptr)
		return ;
	if (is_enabled == 1)
		mlx_put_image_to_window(mlx->mlx_ptr, win_ptr,
			mlx->settings.circle_yes.img, element.x - element.radius, element.y
			- element.radius);
	else
		mlx_put_image_to_window(mlx->mlx_ptr, win_ptr,
			mlx->settings.circle_no.img, element.x - element.radius, element.y
			- element.radius);
}

void	ft_put_circle_specific(t_mlx *mlx, void *win_ptr,
		enum e_screen_size num, bool is_enabled)
{
	if (num == 0)
		ft_put_all_circle_to_win(mlx, win_ptr, is_enabled);
	else if (num == 1)
		ft_put_circle_to_win(mlx, win_ptr, (t_circle){35, 75, 20, 0x0},
			is_enabled);
	else if (num == 2)
		ft_put_circle_to_win(mlx, win_ptr, (t_circle){35, 140, 20, 0x0},
			is_enabled);
	else if (num == 3)
		ft_put_circle_to_win(mlx, win_ptr, (t_circle){35, 210, 20, 0x0},
			is_enabled);
	else if (num == 4)
		ft_put_circle_to_win(mlx, win_ptr, (t_circle){35, 280, 20, 0x0},
			is_enabled);
	else if (num == 5)
		ft_put_circle_to_win(mlx, win_ptr, (t_circle){35, 360, 20, 0x0},
			is_enabled);
	else if (num == 6)
		ft_put_circle_to_win(mlx, win_ptr, (t_circle){35, 435, 20, 0x0},
			is_enabled);
}

void	ft_put_all_circle_to_win(t_mlx *mlx, void *win_ptr, bool is_enabled)
{
	ft_put_circle_to_win(mlx, win_ptr, (t_circle){35, 75, 20, 0x0}, is_enabled);
	ft_put_circle_to_win(mlx, win_ptr, (t_circle){35, 140, 20, 0x0},
		is_enabled);
	ft_put_circle_to_win(mlx, win_ptr, (t_circle){35, 210, 20, 0x0},
		is_enabled);
	ft_put_circle_to_win(mlx, win_ptr, (t_circle){35, 280, 20, 0x0},
		is_enabled);
	ft_put_circle_to_win(mlx, win_ptr, (t_circle){35, 360, 20, 0x0},
		is_enabled);
	ft_put_circle_to_win(mlx, win_ptr, (t_circle){35, 435, 20, 0x0},
		is_enabled);
}
