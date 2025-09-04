/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:10:22 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/04 19:18:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "libft.h"
#include "mlx.h"

static t_mlx	*store_textures_mlx(t_mlx *mlx, t_textures *tex);
static void		copy_path_alt_textures(t_data *data);

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
	copy_path_alt_textures(data);
	if (store_textures_mlx(&data->mlx, &data->map.textures) == NULL
		|| store_textures_mlx(&data->mlx, &data->map.alt_textures) == NULL)
		return (print_error(&data->map, STORE_TEXTURES_IMG));
	if (ft_settings(&data->mlx) == NULL)
		return (print_error(&data->map, FT_SETTINGS));
	settings_hooks(data);
	return (0);
}

// TODO: Used to not check is_alt_textures when exiting, if path exist, free
void	copy_path_alt_textures(t_data *data)
{
	data->map.alt_textures.north.path = data->map.textures.north.path;
	data->map.alt_textures.south.path = data->map.textures.south.path;
	data->map.alt_textures.east.path = data->map.textures.east.path;
	data->map.alt_textures.west.path = data->map.textures.west.path;
	ft_memcpy(&data->map.alt_textures.ceiling, &data->map.textures.ceiling,
		sizeof(t_color));
	ft_memcpy(&data->map.alt_textures.floor, &data->map.textures.floor,
		sizeof(t_color));
}

static int	get_texture_addresses(t_textures *tex)
{
	tex->north.pxls = mlx_get_data_addr(tex->north.img,
			&tex->north.bits_per_pixel, &tex->north.mlx_width,
			&tex->north.endian);
	if (tex->north.pxls == NULL)
		return (0);
	tex->south.pxls = mlx_get_data_addr(tex->south.img,
			&tex->south.bits_per_pixel, &tex->south.mlx_width,
			&tex->south.endian);
	if (tex->south.pxls == NULL)
		return (0);
	tex->east.pxls = mlx_get_data_addr(tex->east.img, &tex->east.bits_per_pixel,
			&tex->east.mlx_width, &tex->east.endian);
	if (tex->east.pxls == NULL)
		return (0);
	tex->west.pxls = mlx_get_data_addr(tex->west.img, &tex->west.bits_per_pixel,
			&tex->west.mlx_width, &tex->west.endian);
	if (tex->west.pxls == NULL)
		return (0);
	return (1);
}

t_mlx	*store_textures_mlx(t_mlx *mlx, t_textures *tex)
{
	tex->north.img = mlx_xpm_file_to_image(mlx->mlx_ptr, tex->north.path,
			&(tex->north.width), &(tex->north.height));
	if (tex->north.img == NULL)
		return (NULL);
	tex->south.img = mlx_xpm_file_to_image(mlx->mlx_ptr, tex->south.path,
			&(tex->south.width), &(tex->south.height));
	if (tex->south.img == NULL)
		return (NULL);
	tex->west.img = mlx_xpm_file_to_image(mlx->mlx_ptr, tex->west.path,
			&(tex->west.width), &(tex->west.height));
	if (tex->west.img == NULL)
		return (NULL);
	tex->east.img = mlx_xpm_file_to_image(mlx->mlx_ptr, tex->east.path,
			&(tex->east.width), &(tex->east.height));
	if (tex->east.img == NULL)
		return (NULL);
	if (get_texture_addresses(tex) == 0)
		return (NULL);
	return (mlx);
}
