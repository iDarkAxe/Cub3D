/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:13:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/23 14:58:35 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include "cub3d.h"

//TODO: REMOVE PROTOTYPE
void		hitside_color(int hitside, const t_pos2 *step, int *color);

#if ENABLE_MINIMAP == 1

static int	calc_line(t_cub *cub, float wall_dist, int x, t_pos2 *line_point)
{
	float	height;
	int		line_draw_height;

	height = cub->win_size.y / wall_dist;
	line_point->y = -height / 2 + cub->win_size.y / 2;
	if (x < cub->minimap_size.x && line_point->y < cub->minimap_size.y)
		line_point->y = cub->minimap_size.y;
	else if (line_point->y < 0)
		line_point->y = 0;
	line_draw_height = height / 2 + cub->win_size.y / 2;
	if (line_draw_height >= cub->win_size.y)
		line_draw_height = cub->win_size.y;
	line_point->x = x;
	line_draw_height -= line_point->y;
	return (line_draw_height);
}

void	draw_column(t_cub *cub, int x, const t_raydata *rdata)
{
	float	wall_dist;
	t_pos2	line_point;
	int		line_draw_height;
	int		color;

	if (rdata->hit_side == 0)
		wall_dist = rdata->side_dist.x - rdata->delta_dist.x;
	else
		wall_dist = rdata->side_dist.y - rdata->delta_dist.y;
	line_draw_height = calc_line(cub, wall_dist, x, &line_point);
	hitside_color(rdata->hit_side, &rdata->step, &color);
	if (line_point.y > 0 && x >= cub->minimap_size.x)
		cubmlx_putvertline(cub, (t_pos2){x, 0}, line_point.y, cub->ceil_color);
	else if (line_point.y > 0)
	{
		cubmlx_putvertline(cub, (t_pos2){x, cub->minimap_size.y}, line_point.y,
			cub->ceil_color);
	}
	cubmlx_putvertline(cub, line_point, line_draw_height, color);
	if ((line_point.y + line_draw_height + 1) < cub->win_size.y)
		cubmlx_putvertline(cub, (t_pos2){x, line_point.y + line_draw_height},
			cub->win_size.y - (line_point.y + line_draw_height),
			cub->floor_color);
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

void	draw_column(t_cub *cub, int x, const t_raydata *rdata)
{
	float	wall_dist;
	t_pos2	line_point;
	int		line_draw_height;
	int		color;

	if (rdata->hit_side == 0)
		wall_dist = rdata->side_dist.x - rdata->delta_dist.x;
	else
		wall_dist = rdata->side_dist.y - rdata->delta_dist.y;
	line_draw_height = calc_line(cub->win_size, wall_dist, x, &line_point);
	hitside_color(rdata->hit_side, &rdata->step, &color);
	if (line_point.y > 0)
		cubmlx_putvertline(cub, (t_pos2){x, 0}, line_point.y, cub->ceil_color);
	cubmlx_putvertline(cub, line_point, line_draw_height, color);
	if ((line_point.y + line_draw_height + 1) < cub->win_size.y)
		cubmlx_putvertline(cub, (t_pos2){x, line_point.y + line_draw_height},
			cub->win_size.y - (line_point.y + line_draw_height),
			cub->floor_color);
}

#endif
