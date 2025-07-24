/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:10:22 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/24 16:29:56 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "libft.h"
#include "mlx.h"

void	settings_hooks(t_mlx *mlx);
t_mlx	*store_textures_mlx(t_mlx *mlx, t_map *map);

int	ft_mlx_init(t_data *data)
{
	if (!data)
		return (-1);
	ft_bzero(&data->mlx, sizeof(t_mlx));
	data->mlx.mouse_x = -1;
	data->mlx.mouse_y = -1;
	data->mlx.settings.state = SIZE_FULL_SCREEN;
	data->mlx.win_size = (t_coordinates){0, 0};
	data->mlx.mlx_ptr = mlx_init();
	if (data->mlx.mlx_ptr == NULL)
		return (-1);
	if (store_textures_mlx(&data->mlx, &data->map) == NULL)
		return (print_error(&data->map, STORE_TEXTURES_IMG));
	if (ft_settings(&data->mlx) == NULL)
		return (print_error(&data->map, FT_SETTINGS));
	settings_hooks(&data->mlx);
	return (0);
}

t_mlx	*store_textures_mlx(t_mlx *mlx, t_map *map)
{
	map->textures.north.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			map->textures.north.path, &(map->textures.north.width),
			&(map->textures.north.height));
	if (map->textures.north.img == NULL)
		return (NULL);
	map->textures.south.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			map->textures.south.path, &(map->textures.south.width),
			&(map->textures.south.height));
	if (map->textures.south.img == NULL)
		return (NULL);
	map->textures.west.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			map->textures.west.path, &(map->textures.west.width),
			&(map->textures.west.height));
	if (map->textures.west.img == NULL)
		return (NULL);
	map->textures.east.img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			map->textures.east.path, &(map->textures.east.width),
			&(map->textures.east.height));
	if (map->textures.east.img == NULL)
		return (NULL);
	return (mlx);
}
