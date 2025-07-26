/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:27:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/26 15:41:35 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

void	cub_free(t_data *data)
{
	// cubmlx_free(&data->mlx);
	ft_mlx_end(&data->mlx);
	if (data->map.map)
	{
		free(data->map.map->walls);
		free(data->map.map);
	}
	free(data);
}

static int	setup_backbuffer(t_data *data)
{
	data->mlx.backbuffer.img = mlx_new_image(data->mlx.mlx_ptr, data->mlx.win_size.x,
			data->mlx.win_size.y);
	if (data->mlx.backbuffer.img == NULL)
		return (0);
	data->mlx.backbuffer.pxls = mlx_get_data_addr(data->mlx.backbuffer.img,
			&data->mlx.backbuffer.bits_per_pixel, &data->mlx.backbuffer.width,
			&data->mlx.backbuffer.endian);
	data->mlx.backbuffer.height = (data->mlx.win_size.x * data->mlx.win_size.y)
		/ data->mlx.backbuffer.width;
	return (1);
}

t_data	*cub_init(t_data *data, int fd)
{
	t_map_raoul	*map;

	if (!data)
		return (NULL);
	map = parse_map(fd);
	if (map == NULL)
		return (NULL);
	data->map.map = map;
	data->mlx.minimap_size.x = data->map.map->width * MINIMAP_TILE_SIZE;
	data->mlx.minimap_size.y = data->map.map->height * MINIMAP_TILE_SIZE;
	if (setup_backbuffer(data) == 0)
		return (ft_mlx_end(&data->mlx), NULL);
	return (data);
}
