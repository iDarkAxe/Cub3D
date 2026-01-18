/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_render_shapes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:03:01 by rdesprez          #+#    #+#             */
/*   Updated: 2026/01/18 11:31:47 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"

void	cubmlx_putvertline(t_data *data, t_pos2 pos, int len,
		unsigned int color)
{
	int		y;
	int		dst;
	char	*px;
	int		step;

	y = pos.y;
	dst = y + len;
	px = data->mlx.backbuffer.pxls + (pos.y * data->mlx.backbuffer.mlx_width + pos.x
			* (data->mlx.backbuffer.nb_bytes_per_pixel));
	step = data->mlx.backbuffer.mlx_width;
	if (dst > data->mlx.win_size.y)
		dst = data->mlx.win_size.y;
	while (y < dst)
	{
		*(unsigned int *)px = color;
		px += step;
		y++;
	}
}

void	cubmlx_putrect(t_data *data, t_pos2 pos, t_pos2 size,
	unsigned int color)
{
	int	x;
	int	y;

	pos_boundary(&pos, data->mlx.win_size);
	if (size.x + pos.x > data->mlx.win_size.x)
		size.x = data->mlx.win_size.x;
	if (size.y + pos.y > data->mlx.win_size.y)
		size.y = data->mlx.win_size.y;
	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
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
