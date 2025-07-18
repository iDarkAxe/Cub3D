/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_render_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:38:10 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/18 12:01:05 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"

void	cubmlx_putline(t_cub *cub, t_pos2 p1, t_pos2 p2, unsigned int color)
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
		if (pos.x >= 0 && pos.x < cub->win_size.x && pos.y >= 0
			&& pos.y < cub->win_size.y)
			cubmlx_putpixel(cub, (int)pos.x, (int)pos.y, color);
		pos.x += delta.x;
		pos.y += delta.y;
		i++;
	}
}
