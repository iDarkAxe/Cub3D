/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:03:01 by rdesprez          #+#    #+#             */
/*   Updated: 2025/08/07 18:16:46 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"
#include "mlx.h"

void	cubmlx_clear(t_mlx *mlx, unsigned int color)
{
	size_t	i;
	size_t	sz;

	sz = mlx->backbuffer.width * mlx->backbuffer.height;
	i = 0;
	while (i < sz)
	{
		*(unsigned int *)(mlx->backbuffer.pxls + i
				* (mlx->backbuffer.bits_per_pixel / 8)) = color;
		i++;
	}
}

void	cubmlx_putpixel(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= data->mlx.win_size.x || y < 0
		|| y >= data->mlx.win_size.y)
		return ;
	dst = data->mlx.backbuffer.pxls + (y * data->mlx.backbuffer.width + x
			* (data->mlx.backbuffer.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	cubmlx_putvertline(t_data *data, t_pos2 pos, int len,
		unsigned int color)
{
	int		y;
	int		dst;
	char	*px;
	int		step;

	y = pos.y;
	dst = y + len;
	px = data->mlx.backbuffer.pxls + (pos.y * data->mlx.backbuffer.width + pos.x
			* (data->mlx.backbuffer.bits_per_pixel / 8));
	step = data->mlx.backbuffer.width;
	while (y < dst)
	{
		if (y >= data->mlx.win_size.y)
			return ;
		*(unsigned int *)px = color;
		px += step;
		y++;
	}
}
