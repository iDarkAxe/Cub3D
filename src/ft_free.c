/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:11:05 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/19 14:03:17 by ppontet          ###   ########lyon.fr   */
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
	if (mlx->settings.circle_no.img)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->settings.circle_no.img);
		mlx->settings.circle_no.img = NULL;
	}
	if (mlx->settings.circle_yes.img)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->settings.circle_yes.img);
		mlx->settings.circle_yes.img = NULL;
	}
	if (mlx->settings.win_ptr)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->settings.win_ptr);
		mlx->settings.win_ptr = NULL;
	}
}
