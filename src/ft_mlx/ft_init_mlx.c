/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:10:22 by ppontet           #+#    #+#             */
/*   Updated: 2025/12/16 20:19:28 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "libft.h"
#include <MLX42.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static mlx_t	*store_textures_mlx(mlx_t *mlx, t_textures *tex);
static void		copy_path_alt_textures(t_data *data);

int	ft_mlx_init(t_data *data)
{
	if (!data)
		return (-1);
	ft_bzero(&data->mlx, sizeof(t_mlx));
	data->mlx.mouse_x = -1;
	data->mlx.mouse_y = -1;
	data->mlx.settings.state = SIZE_1080P;
	// Set default window size
	ft_set_screen_size(&data->mlx, SIZE_1080P);
	// mlx_init creates both the MLX instance and the window
	data->mlx.mlx_ptr = mlx_init(data->mlx.win_size.x, data->mlx.win_size.y, "cub3D", true);
	if (data->mlx.mlx_ptr == NULL)
		return (-1);
	copy_path_alt_textures(data);
	if (store_textures_mlx(data->mlx.mlx_ptr, &data->map.textures) == NULL
		|| store_textures_mlx(data->mlx.mlx_ptr, &data->map.alt_textures) == NULL)
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
	data->map.alt_textures.door.path = data->map.textures.door.path;
	data->map.alt_textures.key.path = data->map.textures.key.path;
	data->map.alt_textures.floor = data->map.textures.floor;
	data->map.alt_textures.ceiling = data->map.textures.ceiling;
}

static int	load_mlx_texture(mlx_t *mlx, t_img *img)
{
	mlx_texture_t	*text;

	if (img->path == NULL)
		return (0);
	text = mlx_load_png(img->path);
	if (text == NULL)
		return (0);
	img->img = mlx_texture_to_image(mlx, text);
	if (img->img == NULL)
	{
		mlx_delete_image(mlx, text);
		return (0);
	}
	img->pxls = (char *)img->img->pixels;
	img->width = img->img->width;
	img->height = img->img->height;
	img->mlx_width = img->img->width;
	img->bits_per_pixel = 32;
	img->nb_bytes_per_pixel = 4;
	img->endian = 0;
	mlx_delete_xpm42(text);
	return (1);
}

static mlx_t	*store_textures_mlx(mlx_t *mlx, t_textures *tex)
{
	if (load_mlx_texture(mlx, &tex->north) == 0)
		return (NULL);
	if (load_mlx_texture(mlx, &tex->south) == 0)
		return (NULL);
	if (load_mlx_texture(mlx, &tex->east) == 0)
		return (NULL);
	if (load_mlx_texture(mlx, &tex->west) == 0)
		return (NULL);

	if (tex->door.path != NULL
		&& load_mlx_texture(mlx, &tex->door) == 0)
		return (NULL);
	if (tex->key.path != NULL
		&& load_mlx_texture(mlx, &tex->key) == 0)
		return (NULL);
	return (mlx);
}
