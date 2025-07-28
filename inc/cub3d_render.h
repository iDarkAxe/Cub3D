/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:50:27 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/28 17:32:40 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_RENDER_H
# define CUB3D_RENDER_H

# include "data_structure.h"
# include <stddef.h>

// RED for now
# define HITSIDE_COLOR_NORTH 0xffff0000
// YELLOW for now
# define HITSIDE_COLOR_SOUTH 0xffffff00
// Green for now
# define HITSIDE_COLOR_WEST 0xff00ff00
// Blue for now
# define HITSIDE_COLOR_EAST 0xff0000ff

t_data		*cub_init(t_data *data);
int			cub_translate_map_hell(t_data *data);
int			cub3d_init_render(t_data *data);
void		cub_render(t_data *data);

void		cub_loop(t_data *data);
void		cub_player_update(t_data *data);
void		cub_render_minimap(t_data *data);
void		draw_column(t_data *data, int x, const t_raydata *rdata);
void		hitwall_loop(const t_data *data, t_raydata *rdata);
void		hitside_color(int hitside, const t_pos2 *step, int *color);
void		raycalc(const t_pos2 win_size, int x, float cam_angle,
				t_raydata *rdata);

// Puting into backbuffer functions
void		cubmlx_putpixel(t_data *data, int x, int y, unsigned int color);
void		cubmlx_putvertline(t_data *data, t_pos2 pos, int len,
				unsigned int color);
void		cubmlx_putline(t_data *data, t_pos2 p1, t_pos2 p2,
				unsigned int color);

// Player movement functions
void		solve_collision_x(t_data *data, float x_vel);
void		solve_collision_y(t_data *data, float y_vel);

// Utility functions
float		absf(float n);
int			max(int a, int b);
t_vec2		vec2rotate(t_vec2 vec, float angle);

#endif
