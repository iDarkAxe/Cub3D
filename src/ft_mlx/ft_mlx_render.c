/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:03:01 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/18 12:00:37 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include "mlx.h"

void	cubmlx_clear(t_cubmlx *mlx, unsigned int color)
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

void	cubmlx_putpixel(t_cub *cub, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= cub->win_size.x || y < 0 || y >= cub->win_size.y)
		return ;
	dst = cub->mlx->backbuffer.pxls + (y * cub->mlx->backbuffer.width + x
			* (cub->mlx->backbuffer.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	cubmlx_putvertline(t_cub *cub, t_pos2 pos, int len,
			unsigned int color)
{
	int		y;
	int		dst;
	char	*px;
	int		step;

	y = pos.y;
	dst = y + len;
	px = cub->mlx->backbuffer.pxls + (pos.y * cub->mlx->backbuffer.width + pos.x
			* (cub->mlx->backbuffer.bits_per_pixel / 8));
	step = cub->mlx->backbuffer.width;
	while (y < dst)
	{
		if (y >= cub->win_size.y)
			return ;
		*(unsigned int *)px = color;
		px += step;
		y++;
	}
}

void	cubmlx_present(t_cubmlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->backbuffer.img, 0, 0);
}
