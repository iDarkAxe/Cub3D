/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:28:00 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/23 13:02:08 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURE_H
# define DATA_STRUCTURE_H

/**
 * @file data_structure.h
 * @brief Header file for all the types and structures of the project.
 *
 */

# include <stddef.h>

typedef struct s_img			t_img;
typedef struct s_textures		t_textures;
typedef struct s_mlx			t_mlx;
typedef struct s_coordinates	t_coordinates;
typedef struct s_map			t_map;
typedef struct s_data			t_data;
typedef struct s_settings		t_settings;

typedef union u_color			t_color;

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

/**
 * @brief Union used to store color information.
 * It can be used to store color in RGBA format
 * or as a separate RGB and alpha values.
 *
 */
union							u_color
{
	int							argb;
	struct
	{
		unsigned char			alpha;
		unsigned char			red;
		unsigned char			green;
		unsigned char			blue;
	};
};

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
	int			x;
	int			y;
}				t_pos2;

/**
 * @brief Structure that handle vector coordinates in 2D space.
 * 
 */
typedef struct s_vec2
{
	float		x;
	float		y;
}				t_vec2;

/**
 * @brief Structure that handle the settings of the game.
 *
 */
struct							s_settings
{
	void						*win_ptr;
	enum e_screen_size			state;
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
	t_coordinates				win_size;
	t_coordinates				minimap_size;
	t_img						backbuffer;
};

/**
 * @brief Structure that handle the map informations.
 *
 */
struct							s_map
{
	char						**file;
	size_t						file_nb_lines;
	char						**map;
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
};

#endif
