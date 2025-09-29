/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/03 17:01:42 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "maze.h"
#include "filter.h"

void	add_filter(t_img *img, int filter)
{
	size_t			pxls;
	size_t			sz;
	union u_color	pixel;
	union u_color	filter_color;

	filter_color.argb = filter;
	sz = img->width * img->height;
	pxls = 0;
	while (pxls < sz)
	{
		pixel.argb = *(int *)(img->pxls + pxls * (img->bits_per_pixel / 8));
		pixel.red = pixel.red + filter_color.red;
		pixel.green = pixel.green + filter_color.green;
		pixel.blue = pixel.blue + filter_color.blue;
		*(int *)(img->pxls + pxls * (img->bits_per_pixel / 8)) = pixel.argb;
		pxls++;
	}
}

void	add_filter_protected(t_img *img, int filter)
{
	size_t			pxls;
	size_t			sz;
	union u_color	pixel;
	union u_color	filter_color;

	filter_color.argb = filter;
	sz = img->width * img->height;
	pxls = 0;
	while (pxls < sz)
	{
		pixel.argb = *(int *)(img->pxls + pxls * (img->bits_per_pixel / 8));
		filter_overflow(&pixel, filter_color);
		*(int *)(img->pxls + pxls * (img->bits_per_pixel / 8)) = pixel.argb;
		pxls++;
	}
}

// Version optimisée pour des filtres simples (teintes monochromes)
void	add_tint(t_img *img, unsigned char red_add, unsigned char green_add,
		unsigned char blue_add)
{
	size_t			pxls;
	size_t			sz;
	union u_color	pixel;

	sz = img->width * img->height;
	pxls = 0;
	while (pxls < sz)
	{
		pixel.argb = *(int *)(img->pxls + pxls * (img->bits_per_pixel / 8));
		pixel.red = pixel.red + red_add;
		pixel.green = pixel.green + green_add;
		pixel.blue = pixel.blue + blue_add;
		*(int *)(img->pxls + pxls * (img->bits_per_pixel / 8)) = pixel.argb;
		pxls++;
	}
}

// Version optimisée pour des filtres simples (teintes monochromes)
void	add_tint_protected(t_img *img, unsigned char red_add,
		unsigned char green_add, unsigned char blue_add)
{
	size_t			pxls;
	size_t			sz;
	union u_color	pixel;
	t_color			filter_color;

	filter_color.red = red_add;
	filter_color.blue = blue_add;
	filter_color.green = green_add;
	sz = img->width * img->height;
	pxls = 0;
	while (pxls < sz)
	{
		pixel.argb = *(int *)(img->pxls + pxls * (img->bits_per_pixel / 8));
		filter_overflow(&pixel, filter_color);
		*(int *)(img->pxls + pxls * (img->bits_per_pixel / 8)) = pixel.argb;
		pxls++;
	}
}
