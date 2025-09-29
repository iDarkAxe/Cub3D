/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:10:22 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/29 15:26:27 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "libft.h"
#include "mlx.h"
#include <unistd.h>

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

t_mlx	*store_textures_mlx(t_mlx *mlx, t_textures *tex)
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
