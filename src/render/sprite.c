/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 09:21:51 by rdesprez          #+#    #+#             */
/*   Updated: 2025/12/16 20:14:36 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_render.h"
#include "data_structure.h"

static void	compute_sprite_position(t_data *data, t_spritedata *sdata,
		t_pos2 pos)
{
	double	inv_cam;

	sdata->sprite.x = pos.x - data->player.pos.x + 0.5f;
	sdata->sprite.y = pos.y - data->player.pos.y + 0.5f;
	inv_cam = 1.0 / (sdata->rdata->plane.x * sdata->rdata->ray_dir.y
			- sdata->rdata->ray_dir.x * sdata->rdata->plane.y);
	sdata->transform.x = inv_cam * (sdata->rdata->ray_dir.y * sdata->sprite.x
			- sdata->rdata->ray_dir.x * sdata->sprite.y);
	sdata->transform.y = inv_cam * (-sdata->rdata->plane.y * sdata->sprite.x
			+ sdata->rdata->plane.x * sdata->sprite.y);
	sdata->sprite_size.x = abs((int)(data->mlx.win_size.y
				/ sdata->transform.y));
	sdata->sprite_size.y = abs((int)(data->mlx.win_size.y
				/ sdata->transform.y));
	sdata->sprite_screen_x = (int)(data->mlx.win_size.x / 2)
		* (1 + sdata->transform.x / sdata->transform.y);
}

static void	determine_draw_region(t_data *data, t_spritedata *sdata)
{
	sdata->draw_start.y = -sdata->sprite_size.y / 2 + data->mlx.win_size.y / 2;
	if (sdata->draw_start.y < 0)
		sdata->draw_start.y = 0;
	sdata->draw_end.y = sdata->sprite_size.y / 2 + data->mlx.win_size.y / 2;
	if (sdata->draw_end.y >= data->mlx.win_size.y)
		sdata->draw_end.y = data->mlx.win_size.y - 1;
	sdata->draw_start.x = -sdata->sprite_size.x / 2 + sdata->sprite_screen_x;
	if (sdata->draw_start.x < 0)
		sdata->draw_start.x = 0;
	sdata->draw_end.x = sdata->sprite_size.x / 2 + sdata->sprite_screen_x;
	if (sdata->draw_end.x >= data->mlx.win_size.x)
		sdata->draw_end.x = data->mlx.win_size.x - 1;
}

static void	draw_sprite_stripe(t_data *data, t_img *img, t_spritedata *sdata,
	int stripe)
{
	t_pos2			tex;
	int				y;
	int				d;
	unsigned int	color;

	tex.x = 256 * (int)((stripe - (-sdata->sprite_size.x / 2
					+ sdata->sprite_screen_x)) * img->width
			/ sdata->sprite_size.x) / 256;
	y = sdata->draw_start.y;
	if (sdata->transform.y > 0 && stripe > 0 && stripe < data->mlx.win_size.x
		&& sdata->transform.y < data->mlx.z_buffer[stripe])
	{
		while (y < sdata->draw_end.y)
		{
			d = y * 256 - data->mlx.win_size.y * 128 + sdata->sprite_size.y
				* 128;
			tex.y = ((d * img->height) / sdata->sprite_size.y) / 256;
			color = *(unsigned int *)(img->pxls + (img->mlx_width * tex.y
						+ tex.x * img->nb_bytes_per_pixel));
			if ((color & 0xff000000) == 0)
				cubmlx_putpixel(data, stripe, y, color);
			y++;
		}
	}
}

static void	render_sprite(t_data *data, t_pos2 pos, t_img *img,
	t_raydata *rdata)
{
	t_spritedata	sdata;
	int				stripe;

	sdata.rdata = rdata;
	compute_sprite_position(data, &sdata, pos);
	determine_draw_region(data, &sdata);
	stripe = sdata.draw_start.x;
	while (stripe < sdata.draw_end.x)
	{
		draw_sprite_stripe(data, img, &sdata, stripe);
		stripe++;
	}
}

void	cub_render_sprites(t_data *data, t_raydata *rdata)
{
	if (data->map.map->door.x > -1)
	{
		render_sprite(data, data->map.map->door, &data->map.textures.door,
			rdata);
	}
	if (data->map.map->key.x > -1)
	{
		render_sprite(data, data->map.map->key, &data->map.textures.key, rdata);
	}
}
