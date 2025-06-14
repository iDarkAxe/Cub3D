/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:08:27 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/17 14:12:41 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

/**
 * @file cube3d.h
 * @brief Header file for the cube3d project.
 *
 * Contains all structures, function prototypes,
 *	and constants used in the project.
 */

# include <stddef.h>
# include <unistd.h>

/**
 * @defgroup Main Main Functions
 * @brief Core functionality of the program.
 * @{
 */

/**
 * @brief Structure used to store an image
 * (buffer that contain image, and size).
 *
 */
typedef struct s_img
{
	void			*ptr;
	int				width;
	int				height;
}					t_img;

/**
 * @brief Strcuture that handle the textures of the game.
 *
 */
typedef struct s_textures
{
	t_img			north;
	t_img			east;
	t_img			west;
	t_img			south;
}					t_textures;

/**
 * @brief Structure that handle the mlx instance.
 *
 */
typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	// void			*win_settings_ptr;
}					t_mlx;

/**
 * @brief Structure used to store the coordinates (positive only).
 *
 */
typedef struct s_coordinates
{
	size_t			x;
	size_t			y;
}					t_coordinates;

/**
 * @brief Structure that handle the map informations.
 *
 */
typedef struct s_map
{
	char			**map;
	int				error;
	size_t			number_of_moves;
	t_coordinates	exit;
	size_t			width;
	size_t			height;
	t_textures		textures;
}					t_map;

/**
 * @brief Structure used to store the mlx and map structures.
 *
 */
typedef struct s_store
{
	t_mlx			*mlx;
	t_map			*map;
}					t_store;

/**
 * @brief Entry point of the program.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int 0 on success, -1 on failure.
 */
int					cube3d(int argc, char **argv);

/**
 * @brief Check the arguments passed to the program.
 *
 * @param argc argument count
 * @param argv array of arguments
 * @return int 1 OK, -1 if error
 */
int					check_args(int argc, char **argv);

/**
 * @brief Exit the program.
 *
 * @param mlx Pointer to the mlx structure.
 * @param map Pointer to the map structure.
 */
void				ft_exit(t_mlx mlx, t_map *map);
/** @} */

/**
 * @defgroup Draw Draw functions
 * @brief All the functions used to draw elements on the screen.
 * @{
 */

/** @} */

/**
 * @defgroup Player Player functions
 * @brief All the functions used to make the player playable.
 * @{
 */

/**
 * @brief Check if the player can move in the given direction.
 *
 * @param map Pointer to the map structure.
 * @param mlx Pointer to the mlx structure.
 * @param direction Direction to move (UP, DOWN, LEFT OR RIGHT).
 */
void				can_player_move(t_mlx *mlx, t_map *map, int direction);
/** @} */

/**
 * @defgroup Hooks Hooks functions
 * @brief All the functions used to handle events.
 * @{
 */

/**
 * @brief Close the program window.
 *
 * @param param Parameter passed to the close function, needs t_mlx pointer.
 * @return int Status code.
 */
int					close_window(void *param);

/**
 * @brief Handle keypress events.
 *
 * @param keycode Keycode of the pressed key.
 * @param param Parameter passed to the function, needs t_store pointer.
 * @return int Keycode of the pressed key.
 */
int					handle_keypress(int keycode, void *param);
/** @} */

/**
 * @defgroup Map_verif Map verification functions
 * @brief All the functions used to verify the map.
 * @{
 */

/**
 * @brief Structure used to store the map dimensions and metadata.
 *
 */
typedef struct s_map_size
{
	int				fd;
	char			*map_name;
	size_t			line_len;
	size_t			prev_line_len;
	size_t			count_line;
	int				error_occured;
}					t_map_size;

/**
 * @brief Check the dimensions of the map.
 *
 * @param map Map structure to modify.
 * @param map_name Name of the map file.
 * @return t_map_size Structure containing the map dimensions and metadata.
 */
t_map				ft_map_check(t_map *map, char *map_name);

/** @} */

/**
 * @defgroup Utils Utils functions
 * @brief All the functions used to help the program.
 * @{
 */

/** @} */

/**
 * @defgroup Print Print functions
 * @brief All the functions used to print nicely.
 * @{
 */

/** @} */

#endif
