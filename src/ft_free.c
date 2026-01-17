/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:11:05 by ppontet           #+#    #+#             */
/*   Updated: 2026/01/17 14:57:10 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "data_structure.h"
#include "filter.h"
#include "mlx.h"
#include <stdlib.h>

#if ENABLE_MULTI_THREAD_RENDERING == 1

void	ft_free_all(t_data *data)
{
	ft_free_settings(&data->mlx);
	ft_free_textures(&data->mlx, &data->map.textures);
	ft_free_textures(&data->mlx, &data->map.alt_textures);
	ft_mlx_end(&data->mlx);
	ft_free_textures_path(&data->map);
	ft_free_file(&data->map);
	ft_free_map(data->map.map);
	cub_render_pool_destroy(&data->pool);
}

#else

void	ft_free_all(t_data *data)
{
	ft_free_settings(&data->mlx);
	ft_free_textures(&data->mlx, &data->map.textures);
	ft_free_textures(&data->mlx, &data->map.alt_textures);
	ft_mlx_end(&data->mlx);
	ft_free_textures_path(&data->map);
	ft_free_file(&data->map);
	ft_free_map(data->map.map);
}

#endif

void	ft_free_map(t_map_raoul *map)
{
	if (!map)
		return ;
	free(map->walls);
	free(map);
	map = NULL;
}

void	ft_free_file(t_map *map)
{
	size_t	index;

	if (map == NULL)
		return ;
	if (map->file != NULL)
	{
		index = 0;
		while (map->file[index])
			free(map->file[index++]);
		free(map->file);
		map->file = NULL;
	}
	if (map->map_2d != NULL)
	{
		free(map->map_2d);
		map->map_2d = NULL;
	}
	map->file_nb_lines = 0;
}
