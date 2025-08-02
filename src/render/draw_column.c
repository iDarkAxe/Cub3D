/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:13:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/08/02 18:15:38 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"
#include <math.h>

static void	get_draw_coords(t_data *data, float line_height, float *draw_coords,
		int x)
{
	if (x < data->mlx.minimap_size.x)
	{
		draw_coords[0] = -line_height / 2 + data->mlx.win_size.y / 2;
		if (draw_coords[0] < data->mlx.minimap_size.y)
			draw_coords[0] = data->mlx.minimap_size.y;
	}
	else
	{
		draw_coords[0] = -line_height / 2 + data->mlx.win_size.y / 2;
		if (draw_coords[0] < 0)
			draw_coords[0] = 0;
	}
	draw_coords[1] = line_height / 2 + data->mlx.win_size.y / 2;
	if (draw_coords[1] >= data->mlx.win_size.y)
		draw_coords[1] = data->mlx.win_size.y - 1;
}

static void	draw_ceiling_and_floor(t_data *data, float *draw_coords, int x)
{
	int	start;

	start = 0;
	if (x < data->mlx.minimap_size.x)
		start = data->mlx.minimap_size.y;
	if (draw_coords[0] >= start)
		cubmlx_putvertline(data, (t_pos2){x, start}, draw_coords[0] - start,
			data->map.textures.ceiling.argb);
	if (draw_coords[1] < data->mlx.win_size.y)
		cubmlx_putvertline(data, (t_pos2){x, draw_coords[1]},
			data->mlx.win_size.y - draw_coords[1] + 1,
			data->map.textures.floor.argb);
}

// FIXME: color weirdness
static void	do_draw_line(t_data *data, t_img *img, t_pos2 *points, int tex_x)
{
	float			step;
	float			tex_pos;
	float			draw_coords[2];
	int				line_height;
	int				tex_y;

	line_height = points[1].y - points[0].y;
	step = 1.f * img->height / line_height;
	get_draw_coords(data, line_height, draw_coords, points[0].x);
	tex_pos = (draw_coords[0] - points[0].y) * step;
	draw_ceiling_and_floor(data, draw_coords, points[0].x);
	while (draw_coords[0] <= draw_coords[1])
	{
		tex_y = (int)tex_pos & (img->height - 1);
		tex_pos += step;
		cubmlx_putpixel(data, points[0].x, draw_coords[0],
			*(unsigned int *)(img->pxls + (img->mlx_width * tex_y
					+ tex_x * (img->bits_per_pixel / 8))));
		draw_coords[0]++;
	}
}

static float	calc_line_and_wall_x(t_pos2 win_size, int x, t_pos2 *line_point,
		const t_raydata *rdata)
{
	float	height;
	float	wall_dist;
	float	wall_x;

	if (rdata->hit_side == 0)
	{
		wall_dist = rdata->side_dist.x - rdata->delta_dist.x;
		wall_x = rdata->pos.y + wall_dist * rdata->ray_dir.y;
	}
	else
	{
		wall_dist = rdata->side_dist.y - rdata->delta_dist.y;
		wall_x = rdata->pos.x + wall_dist * rdata->ray_dir.x;
	}
	height = win_size.y / wall_dist;
	line_point[0].y = -height / 2 + win_size.y / 2;
	line_point[1].y = height / 2 + win_size.y / 2;
	line_point[0].x = x;
	line_point[1].x = x;
	wall_x -= floorf(wall_x);
	return (wall_x);
}

void	draw_column(t_data *data, int x, const t_raydata *rdata)
{
	t_pos2	points[2];
	float	wall_x;
	int		tex_x;
	t_img	*img;

	wall_x = calc_line_and_wall_x(data->mlx.win_size, x, points, rdata);
	img = hitside_texture(&data->map.textures, rdata->hit_side, &rdata->step);
	tex_x = (int)(wall_x * img->width);
	if (!rdata->hit_side && rdata->ray_dir.x > 0)
		tex_x = img->width - tex_x - 1;
	if (rdata->hit_side && rdata->ray_dir.y < 0)
		tex_x = img->width - tex_x - 1;
	do_draw_line(data, img, points, tex_x);
}
