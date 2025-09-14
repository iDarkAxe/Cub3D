/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:33:31 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/14 21:16:01 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H

/**
 * @file ft_print.h
 * @brief Header file for the print functions.
 *
 */

# include "cub3d.h"
# include <unistd.h>

/**
 * @defgroup PRINT_MACROS Print macros functions
 * @brief Print macros used to print.
 * @{
 */

# define RESET "\033[0m"
# define RESET_COLOR RESET
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
/** @} */

/**
 * @defgroup ERROR_TYPES Error types
 * @brief Error types
 * @{
 */

/**
 * @brief Enum used for map related errors
 */
enum	e_map_error
{
	CONFIG_TOO_MANY_PARAMETERS,
	CONFIG_ALREADY_STORED,
	CONFIG_MISSING_PARAMETERS
};

/**
 * @brief Enum used for maze related errors
 */
enum	e_maze_error
{
	MAZE_SIZE_TOO_BIG,
	MAZE_SIZE_TOO_SMALL,
	MAZE_SIZE_NEGATIVE_VALUE,
	MAZE_ARGS_BAD_FORMAT,
};

enum	e_arg_error
{
	ARGS_MISSING_GEN,
	ARGS_DUPLICATE,
	ARGS_NOT_CUB,
	ARGS_NO_MAP,
	ARGS_MAZE_REQUIRED,
	ARGS_DOOR_REQUIRED,
	ARGS_MISSING_KEY,
	ARGS_MISSING_DOOR,
	ARGS_UNRECOGNIZED,
};

/**
 * @brief Enum used for main functions related errors
 */
enum	e_fx_error
{
	FT_MAP_CHECK,
	CHECK_ARGS,
	CONFIG_ERROR,
	STORE_TEXTURES_IMG,
	FT_SETTINGS,
	CUB_INIT_RENDER,
	CUB_INIT,
};
/** @} */

/**
 * @defgroup Print Print functions
 * @brief All the functions used to print.
 * @{
 */

/**
 * @brief Print a position
 * 
 * @param[in] x x axis 
 * @param[in] y y axis 
 * @return ssize_t number of caracter printed
 */
ssize_t	ft_print_position(int x, int y);
/**
 * @brief Print the whole file
 * 
 * @param[in] map map structure
 * @return ssize_t number of caracter printed
 */
ssize_t	ft_print_file(t_map *map);
/**
 * @brief Print the config
 * 
 * @param[in] map map structure
 * @return ssize_t number of caracter printed
 */
ssize_t	ft_print_config(t_map *map);
/**
 * @brief Print the map
 * 
 * @param[in] map map structure
 * @return ssize_t number of caracter printed
 */
ssize_t	ft_print_map(t_map *map);
/**
 * @brief Print the colors of floor and ceiling
 * 
 * @param[in] map map structure 
 */
void	ft_print_floor_ceiling(t_map *map);
/**
 * @brief Print a color
 * 
 * @param[in] color color to print
 */
void	ft_print_color(t_color *color);
/**
 * @brief Print the map visited by the DFS (Depth First Search),
 * DFS is used to search if the exterior is accessible by the player
 * 'x' means visited
 * '.' means not visited
 * 
 * @param[in] visited array of strings referring to visited tiles
 * @param[in] map array of strings referring to original map
 */
void	print_visited(char **visited, char **map);
/**
 * @brief Print the keycode name if registered
 * or just its value if not
 * 
 * @param[in] keycode keycode to print
 */
void	ft_print_key(int keycode);

// ERRORS
/**
 * @brief Print the corresponding map error
 * 
 * @param[in,out] map map structure 
 * @param[in] error error state
 */
void	print_map_error(t_map *map, enum e_map_error error);
/**
 * @brief Print the corresponding maze error
 * 
 * @param[in] error error state 
 */
void	print_maze_error(enum e_maze_error error);
/**
 * @brief Print a special message according to enum
 * 
 * @param[in,out] map map structure 
 * @param[in] error error state
 * @return int 1 if error print OK, 2 otherwise
 */
int		print_error(t_map *map, enum e_fx_error error);
/**
 * @brief Print where a leak is located on the map
 * 
 * @param[in] map array of strings representing map
 * @param[in] y map length
 * @param[in] x map height
 */
void	print_leak_map(char **map, size_t y, size_t x);
/** @} */

#endif
