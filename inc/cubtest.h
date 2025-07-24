/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubtest.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:50:27 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/24 10:55:53 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBTEST_H
# define CUBTEST_H

# include "data_structure.h"
# include <stdbool.h>
# include <stddef.h>

// TODO: NEEDS TO BE MERGED
typedef struct s_map_raoul
{
	int			*walls;
	size_t		width;
	size_t		height;
	t_pos2		start_pos;
	float		start_angle;
}				t_map_raoul;

typedef struct s_cubmlx
{
	void		*mlx;
	void		*win;
	t_img		backbuffer;
}				t_cubmlx;

typedef struct s_input
{
	bool		fwd;
	bool		bckwd;
	bool		left;
	bool		right;
	bool		turn_left;
	bool		turn_right;
}				t_input;

typedef struct s_player
{
	t_vec2		pos;
	float		angle;
	float		fov;
}				t_player;

typedef struct s_cub
{
	t_map_raoul	*map;
	t_cubmlx	mlx;
	t_input		input;
	t_player	player;
	int			ceil_color;
	int			floor_color;
	t_pos2		win_size;
	t_pos2		minimap_size;
}				t_cub;

typedef struct s_raydata
{
	t_vec2		ray_dir;
	t_vec2		side_dist;
	t_vec2		delta_dist;
	t_vec2		pos;
	t_vec2		plane;
	t_pos2		map;
	t_pos2		step;
	int			hit_wall;
	int			hit_side;
	int			ceil_color;
	int			floor_color;
}				t_raydata;

t_map_raoul		*parse_map(int fd);
t_cubmlx		*cubmlx_init(t_cub *cub);
void			*cubmlx_free(t_cubmlx *mlx);
void			cubmlx_present(t_cubmlx *mlx);
void			cubmlx_putpixel(t_cub *cub, int x, int y, unsigned int color);
void			cubmlx_putvertline(t_cub *cub, t_pos2 pos, int len,
					unsigned int color);
void			cubmlx_putline(t_cub *cub, t_pos2 p1, t_pos2 p2,
					unsigned int color);
void			cubmlx_clear(t_cubmlx *mlx, unsigned int color);
t_cub			*cub_init(t_mlx *mlx, int fd);
void			cub_render(t_cub *cub);
void			cub_free(t_cub *cub);

void			cub_loop(t_cub *cub);
void			cub_player_update(t_cub *cub);
void			cub_render_minimap(t_cub *cub);

float			absf(float n);
t_vec2			vec2rotate(t_vec2 vec, float angle);

#endif
