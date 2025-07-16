/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:13:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/16 13:35:05 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include <math.h>

void raycalc(int x, float cam_angle, t_vec2 plane, t_vec2 *side_dist,
			 t_vec2 *delta_dis, t_pos2 *map, t_pos2 *step, const t_vec2 *pos);

void cub_render(t_cub *cub)
{
	int				x;
	float			cam_x;
	t_vec2			plane;
	const t_vec2	pos = cub->player.pos;
	t_pos2			map;
	t_vec2			side_dist;
	t_vec2			delta_dist;
	t_pos2			step;
	int				hit_wall;
	int				hit_side;
	float			wall_dist;
	float			height;
	t_pos2			line_point;
	int				line_draw_height;
	int				color;
	const int		ceil_color = 0xff6494ed;
	const int		floor_color = 0xffdddddd;

	x = 0;
	plane.x = 0;
	plane.y = 0.66f;
	plane = vec2rotate(plane, cub->player.angle);
	while (x < WINDOW_WIDTH)
	{
		map.x = (int)pos.x;
		map.y = (int)pos.y;
		cam_x = 2 * x / (float)WINDOW_WIDTH - 1.f;

		// MARK
		raycalc(x, cub->player.angle, plane, &side_dist, &delta_dist, &map, &step, &pos);
		// END MARK
		
		hit_wall = 0;
		while (!hit_wall)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map.x += step.x;
				hit_side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map.y += step.y;
				hit_side = 1;
			}
			if (map.x < 0 || map.y < 0 || map.x >= (int)cub->map->width || map.y >= (int)cub->map->height)
				break ;
			if (cub->map->walls[map.y * cub->map->width + map.x] > 0)
				hit_wall = 1;
		}
		if (hit_wall == 0)
		{
			cubmlx_putvertline(cub->mlx, (t_pos2){x, 0}, WINDOW_HEIGHT / 2, ceil_color);
			cubmlx_putvertline(cub->mlx, (t_pos2){x, WINDOW_HEIGHT / 2}, WINDOW_HEIGHT / 2, floor_color);
			x++;
			continue ;
		}
		if (hit_side == 0)
			wall_dist = (side_dist.x - delta_dist.x);
		else
			wall_dist = (side_dist.y - delta_dist.y);
		height = (int)(WINDOW_HEIGHT / wall_dist);
		line_point.y = -height / 2 + WINDOW_HEIGHT / 2;
		if (line_point.y < 0)
			line_point.y = 0;
		line_draw_height = height / 2 + WINDOW_HEIGHT / 2;
		if (line_draw_height >= WINDOW_HEIGHT)
			line_draw_height = WINDOW_HEIGHT - 1;
		line_point.x = x;
		line_draw_height = (line_draw_height - line_point.y);
		if (hit_side)
		{
			if (step.y < 0)
				color = 0xffff0000;
			else
				color = 0xffffff00;
		}
		else
		{
			if (step.x < 0)
				color = 0xff00ff00;
			else
				color = 0xff0000ff;
		}
		if (line_point.y > 0)
			cubmlx_putvertline(cub->mlx, (t_pos2){x, 0}, line_point.y, ceil_color);
		cubmlx_putvertline(cub->mlx, line_point, line_draw_height, color);
		if ((line_point.y + line_draw_height + 1) < (WINDOW_HEIGHT))
			cubmlx_putvertline(cub->mlx, (t_pos2){x, line_point.y + line_draw_height}, WINDOW_HEIGHT - (line_point.y + line_draw_height), floor_color);
		x++;
	}
	cub_render_minimap(cub);
	cubmlx_present(cub->mlx);
}
