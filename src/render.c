/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:13:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/16 23:41:16 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include <math.h>

#define CEIL_COLOR 0xff6494ed
#define FLOOR_COLOR 0xffdddddd

// TODO REMOVE all the hardcoded colors
// TODO REMOVE all the hardcoded values
// TODO REMOVE all the hardcoded prototypes
// TODO Check all the pointers values before using them
// Function prototypes
void	raycalc(int x, float cam_angle, t_vec2 plane, t_raydata *rdata);

void	hitside_color(int hitside, const t_pos2 *step, int *color);

void	hitwall_loop(int *hit_wall, t_pos2 *map, t_vec2 *side_dist,
			t_vec2 *delta_dist, t_pos2 *step, const t_cub *cub, int *hit_side);

static int	raycast_column(t_cub *cub, int x, t_vec2 plane, t_raydata *rdata);
static void	draw_column(t_cub *cub, int x, const t_raydata *rdata);
static void calc_line(float wall_dist, int x, t_pos2 *line_point, int *line_draw_height);

void	cub_render(t_cub *cub)
{
	int				x;
	t_vec2			plane;
	t_raydata		rdata;
	
	x = 0;
	rdata.ceil_color = CEIL_COLOR;
	rdata.floor_color = FLOOR_COLOR;
	plane.x = 0;
	plane.y = 0.66f;
	plane = vec2rotate(plane, cub->player.angle);
	while (x < WINDOW_WIDTH)
	{
		if (!raycast_column(cub, x, plane, &rdata))
		{
			cubmlx_putvertline(cub->mlx, (t_pos2){x, 0}, WINDOW_HEIGHT / 2,
				rdata.ceil_color);
			cubmlx_putvertline(cub->mlx, (t_pos2){x, WINDOW_HEIGHT / 2},
				WINDOW_HEIGHT / 2, rdata.floor_color);
			x++;
			continue ;
		}
		draw_column(cub, x, &rdata);
		x++;
	}
	cub_render_minimap(cub);
	cubmlx_present(cub->mlx);
}

static int	raycast_column(t_cub *cub, int x, t_vec2 plane, t_raydata *rdata)
{
	rdata->pos = cub->player.pos;
	rdata->map.x = (int)rdata->pos.x;
	rdata->map.y = (int)rdata->pos.y;
	raycalc(x, cub->player.angle, plane, rdata);
	rdata->hit_wall = 0;
	hitwall_loop(&rdata->hit_wall, &rdata->map, &rdata->side_dist,
		&rdata->delta_dist, &rdata->step, cub, &rdata->hit_side);
	return (rdata->hit_wall);
}

static void calc_line(float wall_dist, int x, t_pos2 *line_point, int *line_draw_height)
{
	float		height;

	height = WINDOW_HEIGHT / wall_dist;
	line_point->y = -height / 2 + WINDOW_HEIGHT / 2;
	if (line_point->y < 0)
		line_point->y = 0;
	*line_draw_height = height / 2 + WINDOW_HEIGHT / 2;
	if (*line_draw_height >= WINDOW_HEIGHT)
		*line_draw_height = WINDOW_HEIGHT;
	line_point->x = x;
	*line_draw_height -= line_point->y;
}

static void	draw_column(t_cub *cub, int x, const t_raydata *rdata)
{
	float		wall_dist;
	t_pos2		line_point;
	int			line_draw_height;
	int			color;

	if (rdata->hit_side == 0)
		wall_dist = rdata->side_dist.x - rdata->delta_dist.x;
	else
		wall_dist = rdata->side_dist.y - rdata->delta_dist.y;
	calc_line(wall_dist, x, &line_point, &line_draw_height);
	hitside_color(rdata->hit_side, &rdata->step, &color);
	if (line_point.y > 0)
		cubmlx_putvertline(cub->mlx, (t_pos2){x, 0}, line_point.y, rdata->ceil_color);
	cubmlx_putvertline(cub->mlx, line_point, line_draw_height, color);
	if ((line_point.y + line_draw_height + 1) < WINDOW_HEIGHT)
		cubmlx_putvertline(cub->mlx, (t_pos2){x, line_point.y + line_draw_height},
			WINDOW_HEIGHT - (line_point.y + line_draw_height), rdata->floor_color);
}
