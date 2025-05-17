/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:39:29 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/17 14:01:30 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "ft_textures.h"

void	*ft_store_textures(t_mlx *mlx, t_map *map)
{
	map->textures.north.ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
			TEXTURE_NORTH, &(map->textures.north.width),
			&(map->textures.north.height));
	if (map->textures.north.ptr == NULL)
		return (NULL);
	map->textures.east.ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
			TEXTURE_EAST, &(map->textures.east.width),
			&(map->textures.east.height));
	if (map->textures.east.ptr == NULL)
		return (NULL);
	map->textures.west.ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
			TEXTURE_WEST, &(map->textures.west.width),
			&(map->textures.west.height));
	if (map->textures.west.ptr == NULL)
		return (NULL);
	map->textures.south.ptr = mlx_xpm_file_to_image(mlx->mlx_ptr,
			TEXTURE_SOUTH, &(map->textures.south.width),
			&(map->textures.south.height));
	if (map->textures.south.ptr == NULL)
		return (NULL);
	return (map);
}
