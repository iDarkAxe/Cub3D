/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:50:27 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/26 15:42:59 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBTEST_H
# define CUBTEST_H

# include "data_structure.h"
# include <stddef.h>

t_map_raoul		*parse_map(int fd);
// void			*cubmlx_free(t_cubmlx *mlx);
// void			cubmlx_present(t_cubmlx *mlx);
void			cubmlx_putpixel(t_data *data, int x, int y, unsigned int color);
void			cubmlx_putvertline(t_data *data, t_pos2 pos, int len,
					unsigned int color);
void			cubmlx_putline(t_data *data, t_pos2 p1, t_pos2 p2,
					unsigned int color);
// void			cubmlx_clear(t_cubmlx *mlx, unsigned int color);
t_data			*cub_init(t_data *data, int fd);
void			cub_render(t_data *data);
void			cub_free(t_data *data);

void			cub_loop(t_data *data);
void			cub_player_update(t_data *data);
void			cub_render_minimap(t_data *data);

float			absf(float n);
t_vec2			vec2rotate(t_vec2 vec, float angle);

#endif
