/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:10:22 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/22 18:25:21 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

// TODO ERMOVE
#include "ft_keys.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>

void	*ft_settings(t_mlx *mlx);

int	ft_mlx_init(t_mlx *mlx)
{
	if (!mlx)
		return (-1);
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return ((void)write(2, "Error\nInit MLX\n", 14), -1);
	mlx->win_settings_ptr = ft_settings(mlx);
	mlx_loop(mlx->mlx_ptr);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->win_size.x,
			mlx->win_size.y, "Cub3d");
	if (mlx->win_ptr == NULL)
		return ((void)write(2, "Error\n", 7), -1);
	mlx_loop(mlx->mlx_ptr);
	if (mlx->mlx_ptr != NULL && mlx->win_ptr != NULL)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->win_ptr = NULL;
	if (mlx->mlx_ptr != NULL)
		mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	mlx->win_ptr = NULL;
	return (0);
}

t_mlx	*store_textures_mlx(t_mlx *mlx, t_map *map)
{
	map->textures.north.ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
			map->config[0], &(map->textures.north.width),
			&(map->textures.north.height));
	if (map->textures.north.ptr == NULL)
		return (NULL);
	map->textures.south.ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
			map->config[0], &(map->textures.south.width),
			&(map->textures.south.height));
	if (map->textures.south.ptr == NULL)
		return (NULL);
	map->textures.west.ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, map->config[0],
			&(map->textures.west.width), &(map->textures.west.height));
	if (map->textures.west.ptr == NULL)
		return (NULL);
	map->textures.east.ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, map->config[0],
			&(map->textures.east.width), &(map->textures.east.height));
	if (map->textures.east.ptr == NULL)
		return (NULL);
	return (mlx);
}
