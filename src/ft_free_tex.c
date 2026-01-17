/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:11:05 by ppontet           #+#    #+#             */
/*   Updated: 2026/01/17 14:57:55 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

void	ft_free_textures(t_mlx *mlx, t_textures *textures)
{
	if (mlx == NULL || mlx->mlx_ptr == NULL)
		return ;
	if (textures->north.img != NULL)
		mlx_destroy_image(mlx->mlx_ptr, textures->north.img);
	if (textures->south.img != NULL)
		mlx_destroy_image(mlx->mlx_ptr, textures->south.img);
	if (textures->west.img != NULL)
		mlx_destroy_image(mlx->mlx_ptr, textures->west.img);
	if (textures->east.img != NULL)
		mlx_destroy_image(mlx->mlx_ptr, textures->east.img);
	if (textures->key.img != NULL)
		mlx_destroy_image(mlx->mlx_ptr, textures->key.img);
	if (textures->door.img != NULL)
		mlx_destroy_image(mlx->mlx_ptr, textures->door.img);
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
