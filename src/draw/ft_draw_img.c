/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 08:48:53 by ppontet           #+#    #+#             */
/*   Updated: 2025/12/16 20:12:34 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "ft_draw.h"
#include "libft.h"

void	ft_put_pixel_to_img(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->pxls + (y * img->width + x * img->nb_bytes_per_pixel);
	ft_memcpy(pixel, &color, sizeof(unsigned int));
}

void	ft_put_pixel_to_img_24bp(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->pxls + (y * img->width) + (x * img->nb_bytes_per_pixel);
	pixel[0] = (char)((color >> 16) & 0xFF);
	pixel[1] = (char)((color >> 8) & 0xFF);
	pixel[2] = (char)(color & 0xFF);
}
