/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:11:05 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/04 18:37:17 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "data_structure.h"
#include "mlx.h"
#include "filter.h"
#include <stdlib.h>

void	ft_free_all(t_data *data)
{
	ft_free_settings(&data->mlx);
	ft_free_textures(&data->mlx, &data->map);
	ft_mlx_end(&data->mlx);
	ft_free_textures_path(&data->map);
	ft_free_file(&data->map);
	ft_free_map(data->map.map);
}

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

void	ft_free_textures(t_mlx *mlx, t_map *map)
{
	if (map == NULL || mlx == NULL || mlx->mlx_ptr == NULL)
		return ;
	if (map->textures.north.img != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->textures.north.img);
		map->textures.north.img = NULL;
	}
	if (map->textures.south.img != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->textures.south.img);
		map->textures.south.img = NULL;
	}
	if (map->textures.west.img != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->textures.west.img);
		map->textures.west.img = NULL;
	}
	if (map->textures.east.img != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->textures.east.img);
		map->textures.east.img = NULL;
	}
	ft_free_alt_textures(mlx, map);
}

void	ft_free_textures_path(t_map *map)
{
	if (map == NULL)
		return ;
	if (map->textures.north.path != NULL)
	{
		free(map->textures.north.path);
		map->textures.north.path = NULL;
	}
	if (map->textures.south.path != NULL)
	{
		free(map->textures.south.path);
		map->textures.south.path = NULL;
	}
	if (map->textures.west.path != NULL)
	{
		free(map->textures.west.path);
		map->textures.west.path = NULL;
	}
	if (map->textures.east.path != NULL)
	{
		free(map->textures.east.path);
		map->textures.east.path = NULL;
	}
}
