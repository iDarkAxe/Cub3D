/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:13:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/22 15:27:13 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include <math.h>

// TODO REMOVE all the hardcoded colors
// TODO REMOVE all the hardcoded values
// TODO REMOVE all the hardcoded prototypes
// TODO Check all the pointers values before using them
// TODO Utilser ENABLE_MINIMAP pour minimap (enlever vars)
// Function prototypes
void		raycalc(const t_pos2 win_size, int x, float cam_angle,
				t_raydata *rdata);

void		hitwall_loop(const t_cub *cub, t_raydata *rdata);

static int	raycast_column(t_cub *cub, int x, t_raydata *rdata);
void		draw_column(t_cub *cub, int x, const t_raydata *rdata);

void	cub_render(t_cub *cub)
{
	int			x;
	t_raydata	rdata;

	x = 0;
	rdata.plane = vec2rotate((t_vec2){0, cub->player.fov * 0.5f},
			cub->player.angle);
	while (x < cub->win_size.x)
	{
		if (!raycast_column(cub, x, &rdata))
		{
			cubmlx_putvertline(cub, (t_pos2){x, 0}, cub->win_size.y / 2,
				cub->ceil_color);
			cubmlx_putvertline(cub, (t_pos2){x, cub->win_size.y / 2},
				cub->win_size.y / 2, cub->floor_color);
			x++;
			continue ;
		}
		draw_column(cub, x, &rdata);
		x++;
	}
	if (ENABLE_MINIMAP == 1)
		cub_render_minimap(cub);
	cubmlx_present(&cub->mlx);
}

static int	raycast_column(t_cub *cub, int x, t_raydata *rdata)
{
	rdata->pos = cub->player.pos;
	rdata->map.x = (int)rdata->pos.x;
	rdata->map.y = (int)rdata->pos.y;
	raycalc(cub->win_size, x, cub->player.angle, rdata);
	rdata->hit_wall = 0;
	hitwall_loop(cub, rdata);
	return (rdata->hit_wall);
}
