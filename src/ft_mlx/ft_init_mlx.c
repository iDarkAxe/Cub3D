/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:10:22 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/13 15:18:46 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>
#include <unistd.h>

static t_mlx	*store_textures_mlx(t_mlx *mlx, t_map *map);

int	ft_mlx_init(t_data *data)
{
	if (!data)
		return (-1);
	ft_bzero(&data->mlx, sizeof(t_mlx));
	data->mlx.mouse_x = -1;
	data->mlx.mouse_y = -1;
	data->mlx.settings.state = SIZE_FULL_SCREEN;
	data->mlx.win_size = (t_pos2){0, 0};
	data->mlx.mlx_ptr = mlx_init();
	if (data->mlx.mlx_ptr == NULL)
		return (-1);
	if (store_textures_mlx(&data->mlx, &data->map) == NULL)
		return (print_error(&data->map, STORE_TEXTURES_IMG));
	if (ft_settings(&data->mlx) == NULL)
		return (print_error(&data->map, FT_SETTINGS));
	settings_hooks(data);
	return (0);
}

static int	load_mlx_texture(t_mlx *mlx, t_img *img)
{
	img->img = mlx_xpm_file_to_image(mlx->mlx_ptr, img->path, &img->width,
			&img->height);
	if (img->img == NULL)
		return (0);
	img->pxls = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->mlx_width, &img->endian);
	if (img->pxls == NULL)
		return (0);
	return (1);
}

t_mlx	*store_textures_mlx(t_mlx *mlx, t_map *map)
{
	if (load_mlx_texture(mlx, &map->textures.north) == 0)
		return (NULL);
	if (load_mlx_texture(mlx, &map->textures.south) == 0)
		return (NULL);
	if (load_mlx_texture(mlx, &map->textures.east) == 0)
		return (NULL);
	if (load_mlx_texture(mlx, &map->textures.west) == 0)
		return (NULL);
	if (map->textures.door.path != NULL
		&& load_mlx_texture(mlx, &map->textures.door) == 0)
		return (NULL);
	if (map->textures.key.path != NULL
		&& load_mlx_texture(mlx, &map->textures.key) == 0)
		return (NULL);
	return (mlx);
}
