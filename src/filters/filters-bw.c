/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters-advanced.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/08 16:10:27 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "filter.h"
#include "ft_keys.h"
#include "libft.h"
#include "maze.h"
#include "mlx.h"
#include "cub3d.h"
#include "ft_printf.h"

static void	convert_texture_to_black_and_white(t_img *img);
static void	convert_color_to_black_and_white(t_color *color);

void	convert_textures_to_black_and_white(t_map *map)
{
	t_textures	*textures;
	t_textures	*orig_textures;

	if (DEBUG_PRINT_TEXTURE_ALTERED)
		ft_printf("Textures converted to Black&White\n");
	if (map->is_alt_textures)
	{
		textures = &map->textures;
		orig_textures = &map->alt_textures;
	}
	else
	{
		textures = &map->alt_textures;
		orig_textures = &map->textures;
	}
	convert_texture_to_black_and_white(&textures->north);
	convert_texture_to_black_and_white(&textures->south);
	convert_texture_to_black_and_white(&textures->east);
	convert_texture_to_black_and_white(&textures->west);
	convert_color_to_black_and_white(&textures->ceiling);
	convert_color_to_black_and_white(&textures->floor);
}

void	convert_color_to_black_and_white(t_color *color)
{
	color->red = color->red * 0.299 + color->green * 0.587 + color->blue
		* 0.114;
	color->green = color->red;
	color->blue = color->red;
}

void	convert_texture_to_black_and_white(t_img *img)
{
	size_t			pxls;
	size_t			sz;
	union u_color	pixel;

	sz = img->width * img->height;
	pxls = 0;
	while (pxls < sz)
	{
		pixel.argb = *(int *)(img->pxls + pxls * (img->bits_per_pixel / 8));
		convert_color_to_black_and_white(&pixel);
		*(int *)(img->pxls + pxls * (img->bits_per_pixel / 8)) = pixel.argb;
		pxls++;
	}
}
