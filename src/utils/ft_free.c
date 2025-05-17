/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:09:09 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/17 12:28:58 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include "mlx.h"

// TODO à adapter

void	free_map(t_map *map, char **map_to_delete, size_t len)
{
	size_t	i;

	i = 0;
	if (map == NULL)
		return ;
	while (i < (len + 1) && i < (map->height + 1))
	{
		if (map_to_delete[i])
		{
			free(map_to_delete[i]);
			map_to_delete[i] = NULL;
		}
		i++;
	}
	if (map_to_delete != NULL)
	{
		free(map_to_delete);
		map_to_delete = NULL;
	}
	free(map);
	map = NULL;
}

void	free_map_textures(t_mlx *mlx, t_map *map)
{
	if (map == NULL)
		return ;
	if (map->textures.north.ptr != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->textures.north.ptr);
		map->textures.north.ptr = NULL;
	}
	if (map->textures.east.ptr != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->textures.east.ptr);
		map->textures.east.ptr = NULL;
	}
	if (map->textures.west.ptr != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->textures.west.ptr);
		map->textures.west.ptr = NULL;
	}
	if (map->textures.south.ptr != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->textures.south.ptr);
		map->textures.south.ptr = NULL;
	}
	free_map(map, map->map, map->height);
}
