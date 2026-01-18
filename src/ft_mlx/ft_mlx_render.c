/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:03:01 by rdesprez          #+#    #+#             */
/*   Updated: 2026/01/18 11:33:15 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"

void	cubmlx_clear(t_mlx *mlx, unsigned int color)
{
	size_t			i;
	size_t			sz;
	unsigned int	*pxls;

	sz = mlx->backbuffer.mlx_width * mlx->backbuffer.height;
	pxls = (unsigned int *)mlx->backbuffer.pxls;
	i = 0;
	while (i < sz)
	{
		pxls[i] = color;
		i++;
	}
}

void	cubmlx_putpixel(t_data *data, int x, int y, unsigned int color)
{
	unsigned int	*pixels;

	pixels = (unsigned int *)data->mlx.backbuffer.pxls;
	pixels[y * data->mlx.backbuffer.width + x] = color;
}

void	cubmlx_putpixel_old(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->mlx.backbuffer.pxls + (y * data->mlx.backbuffer.mlx_width + x
			* (data->mlx.backbuffer.nb_bytes_per_pixel));
	*(unsigned int *)dst = color;
}
