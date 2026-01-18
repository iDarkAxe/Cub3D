/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:27:06 by rdesprez          #+#    #+#             */
/*   Updated: 2026/01/18 11:36:49 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

static int	setup_backbuffer(t_data *data)
{
	data->mlx.backbuffer.img = mlx_new_image(data->mlx.mlx_ptr,
			data->mlx.win_size.x, data->mlx.win_size.y);
	if (data->mlx.backbuffer.img == NULL)
		return (0);
	data->mlx.backbuffer.pxls = mlx_get_data_addr(data->mlx.backbuffer.img,
			&data->mlx.backbuffer.bits_per_pixel,
			&data->mlx.backbuffer.mlx_width, &data->mlx.backbuffer.endian);
	if (data->mlx.backbuffer.pxls == NULL)
		return (0);
	if (data->mlx.backbuffer.bits_per_pixel == 32)
		data->mlx.backbuffer.nb_bytes_per_pixel = 4;
	else
		data->mlx.backbuffer.nb_bytes_per_pixel
			= data->mlx.backbuffer.bits_per_pixel / 8;
	data->mlx.backbuffer.width = data->mlx.win_size.x;
	data->mlx.backbuffer.height = data->mlx.win_size.y;
	data->mlx.z_buffer = ft_calloc(data->mlx.win_size.x, sizeof(float));
	if (data->mlx.z_buffer == NULL)
		return (0);
	return (1);
}

t_data	*cub_init(t_data *data)
{
	if (!data)
		return (NULL);
	if (data->map.map == NULL && cub_translate_map(data) == 0)
		return (NULL);
	data->mlx.minimap_size = (t_pos2){(MINIMAP_NUM_TILES_X - 1)
		* MINIMAP_TILE_SIZE, (MINIMAP_NUM_TILES_Y - 1) * MINIMAP_TILE_SIZE};
	if (setup_backbuffer(data) == 0)
	{
		ft_mlx_end(&data->mlx);
		return (NULL);
	}
	return (data);
}
