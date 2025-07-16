/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:13:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/16 14:55:55 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include <math.h>

// TODO REMOVE all the hardcoded colors
// TODO REMOVE all the hardcoded values
// TODO REMOVE all the hardcoded prototypes
// TODO Check all the pointers values before using them
// Function prototypes
t_vec2	raycalc(int x, float cam_angle, t_vec2 plane, t_vec2 *delta_dis);

void	raycalc_2(t_vec2 *ray_dir, t_vec2 *side_dist, t_vec2 *delta_dis,
			t_pos2 *map, t_pos2 *step, const t_vec2 *pos);

void	hitside_color(int hitside, t_pos2 *step, int *color);

void	hitwall_loop(int *hit_wall, t_pos2 *map, t_vec2 *side_dist,
			t_vec2 *delta_dist, t_pos2 *step, const t_cub *cub, int *hit_side);

void	cub_render(t_cub *cub)
{
	int				x;
	float			cam_x;
	t_vec2			plane;
	const t_vec2	pos = cub->player.pos;
	t_pos2			map;
	t_vec2			side_dist;
	t_vec2			delta_dist;
	t_vec2			ray_dir;
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
		ray_dir = raycalc(x, cub->player.angle, plane, &delta_dist);
		raycalc_2(&ray_dir, &side_dist, &delta_dist, &map, &step, &pos);
		hit_wall = 0;
		hitwall_loop(&hit_wall, &map, &side_dist, &delta_dist, &step, cub,
			&hit_side);
		if (hit_wall == 0)
		{
			cubmlx_putvertline(cub->mlx, (t_pos2){x, 0}, WINDOW_HEIGHT / 2,
				ceil_color);
			cubmlx_putvertline(cub->mlx, (t_pos2){x, WINDOW_HEIGHT / 2},
				WINDOW_HEIGHT / 2, floor_color);
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
			line_draw_height = WINDOW_HEIGHT - 10;
		line_point.x = x;
		line_draw_height = (line_draw_height - line_point.y);
		hitside_color(hit_side, &step, &color);
		if (line_point.y > 0)
			cubmlx_putvertline(cub->mlx, (t_pos2){x, 0}, line_point.y,
				ceil_color);
		cubmlx_putvertline(cub->mlx, line_point, line_draw_height, color);
		if ((line_point.y + line_draw_height + 1) < (WINDOW_HEIGHT))
			cubmlx_putvertline(cub->mlx, (t_pos2){x, line_point.y
				+ line_draw_height}, WINDOW_HEIGHT - (line_point.y
					+ line_draw_height), floor_color);
		x++;
	}
	cub_render_minimap(cub);
	cubmlx_present(cub->mlx);
}
