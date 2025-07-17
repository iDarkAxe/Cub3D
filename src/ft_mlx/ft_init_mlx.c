/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:10:22 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/17 16:35:34 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"

t_mlx	*store_textures_mlx(t_mlx *mlx, t_map *map);

int	ft_mlx_init(t_mlx *mlx)
{
	if (!mlx)
		return (-1);
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->mouse_x = -1;
	mlx->mouse_y = -1;
	mlx->settings_state = SIZE_FULL_SCREEN;
	mlx->win_size = (t_coordinates){0, 0};
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return (-1);
	mlx->win_settings_ptr = ft_settings(mlx);
	return (0);
}

t_mlx	*store_textures_mlx(t_mlx *mlx, t_map *map)
{
	map->textures.north.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			map->config[0], &(map->textures.north.width),
			&(map->textures.north.height));
	if (map->textures.north.img == NULL)
		return (NULL);
	map->textures.south.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			map->config[0], &(map->textures.south.width),
			&(map->textures.south.height));
	if (map->textures.south.img == NULL)
		return (NULL);
	map->textures.west.img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->config[0],
			&(map->textures.west.width), &(map->textures.west.height));
	if (map->textures.west.img == NULL)
		return (NULL);
	map->textures.east.img = mlx_xpm_file_to_image(mlx->mlx_ptr, map->config[0],
			&(map->textures.east.width), &(map->textures.east.height));
	if (map->textures.east.img == NULL)
		return (NULL);
	return (mlx);
}
