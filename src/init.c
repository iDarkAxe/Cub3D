/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:27:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/30 11:48:58 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include "mlx.h"
#include <stdlib.h>

static int	setup_backbuffer(t_data *data)
{
	data->mlx.backbuffer.img = mlx_new_image(data->mlx.mlx_ptr,
			data->mlx.win_size.x, data->mlx.win_size.y);
	if (data->mlx.backbuffer.img == NULL)
		return (0);
	data->mlx.backbuffer.pxls = mlx_get_data_addr(data->mlx.backbuffer.img,
			&data->mlx.backbuffer.bits_per_pixel, &data->mlx.backbuffer.width,
			&data->mlx.backbuffer.endian);
	data->mlx.backbuffer.height = (data->mlx.win_size.x * data->mlx.win_size.y)
		/ data->mlx.backbuffer.width;
	return (1);
}

t_data	*cub_init(t_data *data)
{
	if (!data)
		return (NULL);
	if (cub_translate_map(data) == 0)
		return (NULL);
	data->mlx.minimap_size.x = data->map.map->width * MINIMAP_TILE_SIZE;
	data->mlx.minimap_size.y = data->map.map->height * MINIMAP_TILE_SIZE;
	if (setup_backbuffer(data) == 0)
	{
		ft_mlx_end(&data->mlx);
		return (NULL);
	}
	return (data);
}
