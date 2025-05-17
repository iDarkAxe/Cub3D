/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:05:47 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/17 14:13:37 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_keys.h"
#include "mlx.h"
#include "so_long.h"

void	ft_draw_tile(t_mlx *mlx, t_img img, t_coordinates coords)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img.ptr, img.width
		* (int)coords.x, img.height * (int)coords.y);
}
