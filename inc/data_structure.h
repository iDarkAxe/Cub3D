/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:28:00 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/25 09:47:33 by ppontet          ###   ########lyon.fr   */
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
	SIZE_1080P = 4
};

/**
 * @brief Union used to store color information.
 * It can be used to store color in RGBA format
 * or as a separate RGB and alpha values.
 *
 */
union							u_color
{
	int							rgba;
	struct
	{
		unsigned char			red;
		unsigned char			green;
		unsigned char			blue;
		unsigned char			alpha;
	} s_rgb;
};

/**
 * @brief Structure used to store an image
 * (buffer that contain image, and size).
 *
 */
struct							s_img
{
	char						*path;
	char						*addr;
	void						*ptr;
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
 * @brief Structure that handle the mlx instance.
 *
 */
struct							s_mlx
{
	void						*mlx_ptr;
	void						*win_ptr;
	void						*win_settings_ptr;
	enum e_screen_size			settings_state;
	t_img						circle_yes;
	t_img						circle_no;
	int							mouse_x;
	int							mouse_y;
	t_coordinates				win_size;
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
