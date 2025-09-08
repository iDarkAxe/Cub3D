/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:03:01 by rdesprez          #+#    #+#             */
/*   Updated: 2025/09/08 10:58:29 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"

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

void	cubmlx_putsquare(t_data *data, t_pos2 pos, int size,
	unsigned int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			cubmlx_putpixel(data, pos.x + x, pos.y + y, color);
			x++;
		}
		y++;
	}
}

void	cubmlx_putline(t_data *data, t_pos2 p1, t_pos2 p2, unsigned int color)
{
	t_vec2	delta;
	t_vec2	pos;
	int		length;
	int		i;

	if (absf(p2.x - p1.x) > absf(p2.y - p1.y))
		length = absf(p2.x - p1.x);
	else
		length = absf(p2.y - p1.y);
	delta.x = (float)(p2.x - p1.x) / length;
	delta.y = (float)(p2.y - p1.y) / length;
	pos.x = p1.x + 0.5f;
	pos.y = p1.y + 0.5f;
	i = 0;
	while (i <= length)
	{
		if (pos.x >= 0 && pos.x < data->mlx.win_size.x && pos.y >= 0
			&& pos.y < data->mlx.win_size.y)
			cubmlx_putpixel(data, (int)pos.x, (int)pos.y, color);
		pos.x += delta.x;
		pos.y += delta.y;
		i++;
	}
}
