/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubtest.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:50:27 by rdesprez          #+#    #+#             */
/*   Updated: 2025/07/17 16:30:22 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBTEST_H
# define CUBTEST_H

// TODO AJOUTER 720p dans settings

# include "data_structure.h"
# include <stddef.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define PI 3.141592653589793238462643383279502884197169399375105820974944592307

# define MINIMAP_PLAYER_COLOR 0xffffff00
# define MINIMAP_PLAYER_LINE_OF_SIGHT_COLOR 0xffffff00
# define MINIMAP_PLAYER_CONE_OF_SIGHT_COLOR 0xffffaaaa
# define MINIMAP_FLOOR_COLOR 0xff000000
# define MINIMAP_WALL_COLOR 0xffffffff
# define ENABLE_FIELD_OF_VIEW 1

typedef struct s_pos2
{
	int			x;
	int			y;
}				t_pos2;

typedef struct s_vec2
{
	float		x;
	float		y;
}				t_vec2;

// TODO NEEDS TO BE MERGED
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
	int			fwd;
	int			bckwd;
	int			left;
	int			right;
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
	t_cubmlx	*mlx;
	t_input		input;
	t_player	player;
	int			ceil_color;
	int			floor_color;
	t_pos2		win_size;
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
t_cubmlx		*cubmlx_init(void);
void			*cubmlx_free(t_cubmlx *mlx);
void			cubmlx_present(t_cubmlx *mlx);
void			cubmlx_putpixel(t_cubmlx *mlx, int x, int y,
					unsigned int color);
void			cubmlx_putvertline(t_cubmlx *mlx, t_pos2 pos, int len,
					unsigned int color);
void			cubmlx_putline(t_cubmlx *mlx, t_pos2 p1, t_pos2 p2,
					unsigned int color);
void			cubmlx_clear(t_cubmlx *mlx, unsigned int color);
t_cub			*cub_init(int fd);
void			cub_render(t_cub *cub);
void			cub_free(t_cub *cub);

void			cub_loop(t_cub *cub);
void			cub_render_minimap(t_cub *cub);

float			absf(float n);
t_vec2			vec2rotate(t_vec2 vec, float angle);

#endif
