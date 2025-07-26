/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:13:06 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/26 15:41:39 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"
#include "mlx.h"

// TODO: REMOVE all the hardcoded colors
// TODO: REMOVE all the hardcoded values
// TODO: REMOVE all the hardcoded prototypes
// TODO: Check all the pointers values before using them
// TODO: Utilser ENABLE_MINIMAP pour minimap (enlever vars)
// Function prototypes
void		raycalc(const t_pos2 win_size, int x, float cam_angle,
				t_raydata *rdata);

void		hitwall_loop(const t_data *data, t_raydata *rdata);

static int	raycast_column(t_data *data, int x, t_raydata *rdata);
void		draw_column(t_data *data, int x, const t_raydata *rdata);

void	cub_render(t_data *data)
{
	int			x;
	t_raydata	rdata;

	x = 0;
	rdata.plane = vec2rotate((t_vec2){0, data->player.fov * 0.5f},
			data->player.angle);
	while (x < data->mlx.win_size.x)
	{
		if (!raycast_column(data, x, &rdata))
		{
			cubmlx_putvertline(data, (t_pos2){x, 0}, data->mlx.win_size.y / 2,
				data->map.textures.ceiling.argb);
			cubmlx_putvertline(data, (t_pos2){x, data->mlx.win_size.y / 2},
				data->mlx.win_size.y / 2, data->map.textures.floor.argb);
			x++;
			continue ;
		}
		draw_column(data, x, &rdata);
		x++;
	}
	if (ENABLE_MINIMAP == 1)
		cub_render_minimap(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->mlx.backbuffer.img, 0, 0);
	// cubmlx_present(&data->mlx);
}

static int	raycast_column(t_data *data, int x, t_raydata *rdata)
{
	rdata->pos = data->player.pos;
	rdata->map.x = (int)rdata->pos.x;
	rdata->map.y = (int)rdata->pos.y;
	raycalc(data->mlx.win_size, x, data->player.angle, rdata);
	rdata->hit_wall = 0;
	hitwall_loop(data, rdata);
	return (rdata->hit_wall);
}
