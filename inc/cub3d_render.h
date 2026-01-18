/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:50:27 by rdesprez          #+#    #+#             */
/*   Updated: 2026/01/18 10:23:06 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_RENDER_H
# define CUB3D_RENDER_H

# include "data_structure.h"
# include <stddef.h>

/**
 * @brief Initialize map and backbuffer for rendering
 * 
 * @param[in,out] data data structure
 * @return t_data* data if successful, NULL otherwise
 */
t_data	*cub_init(t_data *data);
/**
 * @brief Convert 2d map string to int vector
 * 
 * @param[in,out] data data structure
 * @return int 1 OK, 0 otherwise
 */
int		cub_translate_map(t_data *data);
/**
 * @brief Init cub for rendering
 * 
 * @param[in,out] data data structure
 * @return int 0 OK, error otherwise
 */
int		cub3d_init_render(t_data *data);
/**
 * @brief Main rendering function
 *
 * @param[in,out] data data structure
 */
void	cub_render(t_data *data);
/**
 * @brief Render a full column on x axis
 * 
 * @param[in,out] data data structure
 * @param[in] x x axis
 * @param[in] plane camera plane
 */
void	cub_render_x_column(t_data *data, int x, const t_vec2 *plane);
/**
 * @brief Initialize the thread pool
 * 
 * @param[out] pool thread pool
 * @return bool true if error, false otherwise
 */
bool	cub_render_pool_init(t_render_pool *pool);
/**
 * @brief Fill the thread pool with work
 * 
 * @param[in,out] data data structure
 * @param[in,out] plane camera plane
 */
void	fill_thread_pool(t_data *data, t_vec2 plane);
/**
 * @brief Waits for each thread to finish it's work
 * 
 * @param[in,out] pool thread pool
 */
void	wait_thread_pool(t_render_pool *pool);
/**
 * @brief Main loop function. Handles player update logic and rendering
 * 
 * @param[in,out] data data structure
 */
void	cub_loop(t_data *data);
/**
 * @brief Updates player based on input
 * 
 * @param[in,out] data data structure
 */
void	cub_player_update(t_data *data);
/**
 * @brief Render the minimap
 * 
 * @param[in,out] data data structure
 */
void	cub_render_minimap(t_data *data);
/**
 * @brief Calculate the endpoint of a ray on the minimap
 * 
 * @param[in] data data structure
 * @param[in] origin origin point of the ray
 * @param[in] angle angle of the ray
 * @param[in] dist distance of the ray
 * @return t_pos2 endpoint of the ray
 */
t_pos2	minimap_ray_endpoint(t_data *data, t_pos2 origin, float angle,
			float dist);
/**
 * @brief Perform a raycast on the minimap
 * 
 * @param[in] data data structure
 * @param[in] ray_angle angle of the ray
 * @return float distance to the wall hit
 */
float	minimap_raycast(t_data *data, float ray_angle);
/**
 * @brief Draw a column of pixels from a raycast result
 * 
 * @param[in,out] data data structure
 * @param[in] x x axis column
 * @param[in,out] rdata structure to handle important values for rendering 
 */
void	draw_column(t_data *data, int x, const t_raydata *rdata);
/**
 * @brief Check which wall will be hit
 * 
 * @param[in,out] data data structure
 * @param[in,out] rdata structure to handle important values for rendering 
 */
void	hitwall_loop(const t_data *data, t_raydata *rdata);
/**
 * @brief Function to select the texture based on the hit side
 * and step direction.
 * 
 * @param[in] tex pointer to texture structure
 * @param[in] hitside hitside
 * @param[in] step step direction
 */
t_img	*hitside_texture(t_textures *tex, int hitside, const t_pos2 *step);
/**
 * @brief Function to calculate rays using window size and camera angle
 * 
 * @param[in] win_size window size
 * @param[in] x x axis column
 * @param[in] cam_angle camera angle
 * @param[in,out] rdata structure to handle important values for rendering 
 */
void	raycalc(const t_pos2 win_size, int x, float cam_angle,
			t_raydata *rdata);

/**
 * @brief Render the door and key sprites
 * 
 * @param[in,out] data data structure
 * @param[in,out] rdata raydata structure
 */
void	cub_render_sprites(t_data *data, t_raydata *rdata);

/**
 * @defgroup Backbuffer Backbuffer Manipulation
 * @brief Backbuffer functions used to manipulate and place pixels onto it.
 * @{
 *
 */

/**
 * @brief Clear the backbuffer with a specific color.
 * 
 * @param[in,out] mlx mlx structure
 * @param[in] color color
 */
void	cubmlx_clear(t_mlx *mlx, unsigned int color);

/**
 * @brief Puts a pixel onto the backbuffer, 
 * assumes multiple things like x and y are valid, 
 * the backbuffer is properly allocated,
 * and that bytes per pixel is 4.
 * Faster than cubmlx_putpixel_old without optimizations 
 * (but no differences in -O3).
 * 
 * @param[in,out] data data structure
 * @param[in] x x axis
 * @param[in] y y axis
 * @param[in] color color
 */
void	cubmlx_putpixel(t_data *data, int x, int y, unsigned int color);

/**
 * @brief Puts a pixel onto the backbuffer, 
 * assumes multiple things like x and y are valid, 
 * the backbuffer is properly allocated,
 * 
 * @param[in,out] data data structure
 * @param[in] x x axis
 * @param[in] y y axis
 * @param[in] color color
 */
void	cubmlx_putpixel_old(t_data *data, int x, int y, unsigned int color);

/**
 * @brief Puts a vertical line on the backbuffer. Optimized for vertical lines.
 * 
 * @param[in,out] data data structure
 * @param[in] pos coordinates of starting point of the line
 * @param[in] len len of the line
 * @param[in] color color
 */
void	cubmlx_putvertline(t_data *data, t_pos2 pos, int len,
			unsigned int color);

/**
 * @brief Puts a rectangle onto the backbuffer
 *
 * @param[in,out] data structure
 * @param[in] pos starting point
 * @param[in] size rectangle width and height
 * @param[in] color color
 */
void	cubmlx_putrect(t_data *data, t_pos2 pos, t_pos2 size,
			unsigned int color);

/**
 * @brief Puts a line onto the backbuffer
 * 
 * @param[in,out] data data structure
 * @param[in] p1 coordinates of starting point of the line
 * @param[in] p2 coordinates of ending point of the line
 * @param[in] color color
 */
void	cubmlx_putline(t_data *data, t_pos2 p1, t_pos2 p2, unsigned int color);
/** @} */

/**
 * @defgroup Player Player functions
 * @brief Functions used to make the player playable (no-clipping).
 * @{
 */

/**
 * @brief Solver of collision on x axis
 * 
 * @param[in,out] data data structure
 * @param[in] x_vel velocity on x axis
 */
void	solve_collision_x(t_data *data, float x_vel);

/**
 * @brief Solver of collision on y axis
 * 
 * @param[in,out] data data structure
 * @param[in] y_vel velocity on y axis
 */
void	solve_collision_y(t_data *data, float y_vel);

/**
 * @brief Solver of collision on x and y using steps smaller than 1 unit,
 * To use only when moving faster than 1 unit, when
 * MOVEMENT_SPEED_FWD_BWD >= 1.0f or MOVEMENT_SPEED_LEFT_RIGHT >= 1.0f 
 * 
 * @param[in,out] data data structure
 * @param[in] vel_x velocity on x axis
 * @param[in] vel_y velocity on y axis
 */
void	resolve_collision_steps(t_data *data, float vel_x, float vel_y);

/**
 * @brief Limit a position, if it is outside, it's modified
 * 
 * @param[in,out] pos pos to verify 
 * @param[in] limit limit to not exceed
 */
void	pos_boundary(t_pos2 *pos, const t_pos2 limit);
/** @} */

/**
 * @defgroup Utils Utils functions
 * @brief All the functions used to help the program.
 * @{
 */

/**
 * @brief Returns the absolute value of a float
 * 
 * @param[in] n value
 * @return float absolute value of n 
 */
float	absf(float n);

/**
 * @brief Returns the absolute value of an int
 *
 * @param[in] n value
 * @return float absolute vale of n
 */
int		abs(int n);

/**
 * @brief Returns the highest value between a and b
 * 
 * @param[in] a first value
 * @param[in] b second value
 * @return int highest between a and b
 */
int		max(int a, int b);

/**
 * @brief Returns the lowest value between doubles a and b
 *
 * @param[in] a first value
 * @param[in] b second value
 * @return int lowest between a and b
 */
double	mind(double a, double b);

/**
 * @brief Returns a new vector rotated according to the angle
 * 
 * @param[in] vec vector
 * @param[in] angle angle
 * @return t_vec2 vector rotated
 */
t_vec2	vec2rotate(t_vec2 vec, float angle);
/** @} */

#endif
