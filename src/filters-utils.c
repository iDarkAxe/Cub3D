/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/06 12:43:17 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "filter.h"
#include "ft_keys.h"
#include "maze.h"
#include "mlx.h"

void	filter_overflow(t_color *pixel, t_color filter)
{
	if (pixel->red + filter.red > 255)
		pixel->red = 255;
	else
		pixel->red = pixel->red + filter.red;
	if (pixel->blue + filter.blue > 255)
		pixel->blue = 255;
	else
		pixel->blue = pixel->blue + filter.blue;
	if (pixel->green + filter.green > 255)
		pixel->green = 255;
	else
		pixel->green = pixel->green + filter.green;
}

void	apply_filters_on_textures(t_textures *textures)
{
	int	temp;

	if (RANDOM_FILTER_ON_ALL == 0)
	{
		temp = ft_rand();
		temp = -temp & 0xEEEEEEEE;
		add_filter(&textures->north, temp);
		add_filter(&textures->south, temp);
		add_filter(&textures->east, temp);
		add_filter(&textures->west, temp);
	}
	else
	{
		add_filter(&textures->north, -ft_rand() & 0xEEEEEEEE);
		add_filter(&textures->south, -ft_rand() & 0xEEEEEEEE);
		add_filter(&textures->east, -ft_rand() & 0xEEEEEEEE);
		add_filter(&textures->west, -ft_rand() & 0xEEEEEEEE);
	}
}

void	change_filter(t_data *data, int keycode)
{
	if (keycode == KEY_V && data->map.is_alt_textures == 0)
		apply_filters_on_textures(&data->map.alt_textures);
	else if (keycode == KEY_V)
		apply_filters_on_textures(&data->map.textures);
	if (keycode == KEY_C)
		swap_textures(&data->map);
	if (keycode == KEY_X)
	{
		convert_textures_to_black_and_white(&data->map);
		swap_textures(&data->map);
	}
}

void	swap_textures(t_map *map)
{
	t_textures	temp;

	if (!map)
		return ;
	if (!map->alt_textures.north.pxls || !map->alt_textures.south.pxls
		|| !map->alt_textures.east.pxls || !map->alt_textures.west.pxls)
		return ;
	if (!map->textures.north.pxls || !map->textures.south.pxls
		|| !map->textures.east.pxls || !map->textures.west.pxls)
		return ;
	temp = map->textures;
	map->textures = map->alt_textures;
	map->alt_textures = temp;
	map->is_alt_textures = !map->is_alt_textures;
}

void	ft_free_alt_textures(t_mlx *mlx, t_map *map)
{
	if (map == NULL || mlx == NULL || mlx->mlx_ptr == NULL)
		return ;
	if (map->alt_textures.north.img != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->alt_textures.north.img);
		map->alt_textures.north.img = NULL;
	}
	if (map->alt_textures.south.img != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->alt_textures.south.img);
		map->alt_textures.south.img = NULL;
	}
	if (map->alt_textures.west.img != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->alt_textures.west.img);
		map->alt_textures.west.img = NULL;
	}
	if (map->alt_textures.east.img != NULL)
	{
		mlx_destroy_image(mlx->mlx_ptr, map->alt_textures.east.img);
		map->alt_textures.east.img = NULL;
	}
}
