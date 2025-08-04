/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:28:00 by ppontet           #+#    #+#             */
/*   Updated: 2025/08/04 18:23:42 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURE_H
# define DATA_STRUCTURE_H

/**
 * @file data_structure.h
 * @brief Header file for all the types and structures of the project.
 *
 */

# include <endian.h>
# include <stdbool.h>
# include <stddef.h>

typedef struct s_img			t_img;
typedef struct s_textures		t_textures;
typedef struct s_mlx			t_mlx;
typedef struct s_coordinates	t_coordinates;
typedef struct s_map			t_map;
typedef struct s_data			t_data;
typedef struct s_settings		t_settings;

typedef union u_color			t_color;
typedef struct s_raydata		t_raydata;
typedef struct s_input			t_input;
typedef struct s_player			t_player;
typedef struct s_map_raoul		t_map_raoul;

/**
 * @brief Enum used to store the screen size.
 * It is used to set the screen size in the settings.
 *
 */
enum							e_screen_size
{
	SIZE_NONE = 0,
	SIZE_FULL_SCREEN = 1,
	SIZE_4K = 2,
	SIZE_2K = 3,
	SIZE_1080P = 4,
	SIZE_720P = 5,
	SIZE_480P = 6,
};

# if __BYTE_ORDER == __BIG_ENDIAN

/**
 * @brief Union used to store color information.
 * It can be used to store color in RGBA format
 * or as a separate RGB and alpha values.
 * Used for big-endian systems.
 */
union							u_color
{
	int							argb;
	struct __attribute__((packed))
	{
		unsigned char			alpha;
		unsigned char			red;
		unsigned char			green;
		unsigned char			blue;
	};
};

# else

/**
 * @brief Union used to store color information.
 * It can be used to store color in RGBA format
 * or as a separate RGB and alpha values.
 * Used for little-endian systems.
 */
union							u_color
{
	int							argb;
	struct __attribute__((packed))
	{
		unsigned char			blue;
		unsigned char			green;
		unsigned char			red;
		unsigned char			alpha;
	};
};
# endif

/**
 * @brief Structure used to store an image
 * (buffer that contain image, and size).
 *
 */
struct							s_img
{
	char						*path;
	char						*pxls;
	void						*img;
	int							width;
	int							height;
	int							bits_per_pixel;
	int							endian;
};

/**
 * @brief Strcuture that handle the textures of the game.
 *
 */
struct							s_textures
{
	t_img						north;
	t_img						east;
	t_img						west;
	t_img						south;
	t_color						floor;
	t_color						ceiling;
};

/**
 * @brief Structure used to store the coordinates (positive only).
 *
 */
struct							s_coordinates
{
	size_t						x;
	size_t						y;
};

/**
 * @brief Structure that handle positions in the map.
 * Same as t_coordinates but with signed integers.
 */
typedef struct s_pos2
{
	int							x;
	int							y;
}								t_pos2;

/**
 * @brief Structure that handle vector coordinates in 2D space.
 *
 */
typedef struct s_vec2
{
	float						x;
	float						y;
}								t_vec2;

/**
 * @brief Structure that handle the input of the player.
 *
 */
struct							s_input
{
	bool						fwd;
	bool						bckwd;
	bool						left;
	bool						right;
	bool						turn_left;
	bool						turn_right;
	bool						collision;
	bool						minimap;
	bool						fov;
	int							mouse_input;
	int							skip_next_mouse_input;
	int							delta_mouse_x;
};

/**
 * @brief Structure that handle the player information.
 *
 */
struct							s_player
{
	t_vec2						pos;
	float						angle;
	float						fov;
};

/**
 * @brief Structure that handle the settings of the game.
 *
 */
struct							s_settings
{
	void						*win_ptr;
	enum e_screen_size			state;
	t_img						background;
	t_img						circle_yes;
	t_img						circle_no;
};

/**
 * @brief Structure that handle the mlx instance.
 *
 */
struct							s_mlx
{
	void						*mlx_ptr;
	void						*win_ptr;
	t_settings					settings;
	int							mouse_x;
	int							mouse_y;
	t_pos2						win_size;
	t_pos2						minimap_size;
	t_img						backbuffer;
};

struct s_map_raoul
{
	int							*walls;
	size_t						width;
	size_t						height;
	t_pos2						start_pos;
	float						start_angle;
};

/**
 * @brief Structure that handle the map informations.
 *
 */
struct							s_map
{
	char						**file;
	size_t						file_nb_lines;
	char						**map_2d;
	t_map_raoul					*map;
	char						*config[6];
	int							error;
	size_t						number_of_moves;
	t_coordinates				exit;
	t_textures					textures;
};

/**
 * @brief Structure used to store the mlx and map structures.
 *
 */
struct							s_data
{
	t_mlx						mlx;
	t_map						map;
	t_input						input;
	t_player					player;
};

/**
 * @brief Structure used to store the raycasting data.
 * It contains all the information needed to cast a ray.
 *
 */
struct							s_raydata
{
	t_vec2						ray_dir;
	t_vec2						side_dist;
	t_vec2						delta_dist;
	t_vec2						pos;
	t_vec2						plane;
	t_pos2						map;
	t_pos2						step;
	int							hit_wall;
	int							hit_side;
	int							ceil_color;
	int							floor_color;
};

#endif
