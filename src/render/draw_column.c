/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:13:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/26 16:12:48 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"

#if ENABLE_MINIMAP == 1

static int	calc_line(t_data *data, float wall_dist, int x, t_pos2 *line_point)
{
	float	height;
	int		line_draw_height;

	height = data->mlx.win_size.y / wall_dist;
	line_point->y = -height / 2 + data->mlx.win_size.y / 2;
	if (x < data->mlx.minimap_size.x
		&& line_point->y < data->mlx.minimap_size.y)
		line_point->y = data->mlx.minimap_size.y;
	else if (line_point->y < 0)
		line_point->y = 0;
	line_draw_height = height / 2 + data->mlx.win_size.y / 2;
	if (line_draw_height >= data->mlx.win_size.y)
		line_draw_height = data->mlx.win_size.y;
	line_point->x = x;
	line_draw_height -= line_point->y;
	return (line_draw_height);
}

void	draw_column(t_data *data, int x, const t_raydata *rdata)
{
	float	wall_dist;
	t_pos2	line_point;
	int		line_draw_height;
	int		color;

	if (rdata->hit_side == 0)
		wall_dist = rdata->side_dist.x - rdata->delta_dist.x;
	else
		wall_dist = rdata->side_dist.y - rdata->delta_dist.y;
	line_draw_height = calc_line(data, wall_dist, x, &line_point);
	hitside_color(rdata->hit_side, &rdata->step, &color);
	if (line_point.y > 0 && x >= data->mlx.minimap_size.x)
		cubmlx_putvertline(data, (t_pos2){x, 0}, line_point.y,
			data->map.textures.ceiling.argb);
	else if (line_point.y > 0)
	{
		cubmlx_putvertline(data, (t_pos2){x, data->mlx.minimap_size.y},
			line_point.y, data->map.textures.ceiling.argb);
	}
	cubmlx_putvertline(data, line_point, line_draw_height, color);
	if ((line_point.y + line_draw_height + 1) < data->mlx.win_size.y)
		cubmlx_putvertline(data, (t_pos2){x, line_point.y + line_draw_height},
			data->mlx.win_size.y - (line_point.y + line_draw_height),
			data->map.textures.floor.argb);
}

#else

static int	calc_line(t_pos2 win_size, float wall_dist, int x,
		t_pos2 *line_point)
{
	float	height;
	int		line_draw_height;

	height = win_size.y / wall_dist;
	line_point->y = -height / 2 + win_size.y / 2;
	if (line_point->y < 0)
		line_point->y = 0;
	line_draw_height = height / 2 + win_size.y / 2;
	if (line_draw_height >= win_size.y)
		line_draw_height = win_size.y;
	line_point->x = x;
	line_draw_height -= line_point->y;
	return (line_draw_height);
}

void	draw_column(t_data *data, int x, const t_raydata *rdata)
{
	float	wall_dist;
	t_pos2	line_point;
	int		line_draw_height;
	int		color;

	if (rdata->hit_side == 0)
		wall_dist = rdata->side_dist.x - rdata->delta_dist.x;
	else
		wall_dist = rdata->side_dist.y - rdata->delta_dist.y;
	line_draw_height = calc_line(data->mlx.win_size, wall_dist, x, &line_point);
	hitside_color(rdata->hit_side, &rdata->step, &color);
	if (line_point.y > 0)
		cubmlx_putvertline(data, (t_pos2){x, 0}, line_point.y,
			data->map.textures.ceiling.argb);
	cubmlx_putvertline(data, line_point, line_draw_height, color);
	if ((line_point.y + line_draw_height + 1) < data->mlx.win_size.y)
		cubmlx_putvertline(data, (t_pos2){x, line_point.y + line_draw_height},
			data->mlx.win_size.y - (line_point.y + line_draw_height),
			data->map.textures.floor.argb);
}

#endif
