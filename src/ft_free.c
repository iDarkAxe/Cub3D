/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:11:05 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/25 13:02:19 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "mlx.h"
#include <stdlib.h>

void	ft_free_file(t_map *map);
void	ft_free_textures(t_mlx *mlx, t_map *map);
void	ft_free_textures_path(t_map *map);
void	ft_mlx_end(t_mlx *mlx);
void	ft_free_settings(t_mlx *mlx);

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
	if (map->map != NULL)
	{
		free(map->map);
		map->map = NULL;
	}
	map->file_nb_lines = 0;
}

void	ft_free_textures(t_mlx *mlx, t_map *map)
{
	if (map == NULL || mlx == NULL)
		return ;
	if (map->textures.north.ptr != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->textures.north.ptr);
		map->textures.north.ptr = NULL;
	}
	if (map->textures.south.ptr != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->textures.south.ptr);
		map->textures.south.ptr = NULL;
	}
	if (map->textures.west.ptr != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->textures.west.ptr);
		map->textures.west.ptr = NULL;
	}
	if (map->textures.east.ptr != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->textures.east.ptr);
		map->textures.east.ptr = NULL;
	}
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

void	ft_mlx_end(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->mlx_ptr != NULL && mlx->win_ptr != NULL)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->win_ptr = NULL;
	if (mlx->mlx_ptr != NULL)
		mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	mlx->win_ptr = NULL;
}

void	ft_free_settings(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->circle_no.ptr)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->circle_no.ptr);
		mlx->circle_no.ptr = NULL;
	}
	if (mlx->circle_yes.ptr)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->circle_yes.ptr);
		mlx->circle_yes.ptr = NULL;
	}
	if (mlx->win_settings_ptr)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_settings_ptr);
		mlx->win_settings_ptr = NULL;
	}
}
