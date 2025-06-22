/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:10:22 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/22 12:17:05 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"

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
	map->textures.west.ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
			map->config[0], &(map->textures.west.width),
			&(map->textures.west.height));
	if (map->textures.west.ptr == NULL)
		return (NULL);
	map->textures.east.ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
			map->config[0], &(map->textures.east.width),
			&(map->textures.east.height));
	if (map->textures.east.ptr == NULL)
		return (NULL);
	return (mlx);
}
