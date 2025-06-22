/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:08:27 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/17 14:12:41 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/**
 * @file cub3d.h
 * @brief Header file for the cub3d project.
 *
 * Contains all function prototypes used in the project.
 */

# include "data_structure.h"
# include <stddef.h>
# include <unistd.h>

/**
 * @defgroup Main Main Functions
 * @brief Core functionality of the program.
 * @{
 */

/**
 * @brief Entry point of the program.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int 0 on success, -1 on failure.
 */
int				cub3d(int argc, char **argv);

/**
 * @brief Check the arguments passed to the program.
 *
 * @param argc argument count
 * @param argv array of arguments
 * @return int 1 OK, -1 if error
 */
int				check_args(int argc, char **argv);

/**
 * @brief Fill the config region of the file
 *
 * @param map map structure
 * @return char** NULL if error, config otherwise
 */
char			**fill_config_region(t_map *map);

/**
 * @brief Fill the map region of the file
 *
 * @param map map structure
 * @return char** NULL if error, map otherwise
 */
char			**fill_map_region(t_map *map);

/**
 * @brief Read the map file line by line and return an array of strings.
 *
 * @param map_name map file name to read
 * @return char** array of strings containing the map lines
 */
char			**read_file_lines(t_map *map, char *map_name);

/**
 * @brief Simple function to count the number of lines in a file.
 *
 * @param file_name file name to count lines in
 * @return size_t
 */
size_t			count_file_lines(char *file_name);

/**
 * @brief Store the textures names in the structure
 *
 * @param map map structure
 * @return char* NULL if error, OK otherwise
 */
char			*store_textures_names(t_map *map);

/**
 * @brief Exit the program.
 *
 * @param mlx Pointer to the mlx structure.
 * @param map Pointer to the map structure.
 */
void			ft_exit(t_mlx mlx, t_map *map);
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
void			can_player_move(t_mlx *mlx, t_map *map, int direction);
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
int				close_window(void *param);

/**
 * @brief Handle keypress events.
 *
 * @param keycode Keycode of the pressed key.
 * @param param Parameter passed to the function, needs t_store pointer.
 * @return int Keycode of the pressed key.
 */
int				handle_keypress(int keycode, void *param);
/** @} */

/**
 * @defgroup Map_verif Map verification functions
 * @brief All the functions used to verify the map.
 * @{
 */

/**
 * @brief Check the dimensions of the map.
 *
 * @param map Map structure to modify.
 * @param map_name Name of the map file.
 * @return t_map_size Structure containing the map dimensions and metadata.
 */
t_map			ft_map_check_dimensions(t_map *map, char *map_name);

/**
 * @brief Check if the config is properly formatted or not
 *
 * @param map map structure
 * @return t_map map structure
 */
t_map			ft_check_config(t_map *map);

/**
 * @brief Check the floor and ceiling colors
 *
 * @param map map structure
 * @return t_map map structure
 */
t_map			ft_check_floor_ceiling(t_map *map);

/**
 * @brief Return a positive number if a config line is detected
 *
 * @param line line to check
 * @return int 0 not config line, positive number otherwise
 */
size_t			is_config_line(char *line);

/**
 * @brief Check if the map has only acceptable characters 
 * and if there is borders everywhere, as it should be
 * 
 * @param map map structure
 * @return t_map map structure
 */
t_map			check_map_chars_borders(t_map *map);

/**
 * @brief Find the position of the player with charset in the map
 * 
 * @param map map structure
 * @param charset strings of autorized characters for player
 * @return t_coordinates coordinates of player
 */
t_coordinates	find_position(t_map *map, const char *charset);

/**
 * @brief Validate if the map has unclosed holes or an unfinished outer layer
 * 
 * @param map map structure
 * @return int 1 OK, error otherwise
 */
int				validate_map(t_map *map);

/**
 * @brief Check if a character is walkable or not
 * 
 * @param c character
 * @return int 1 OK, error otherwise
 */
int				is_walkable(char c);

/**
 * @brief Check if a position is in bounds of map or not
 * 
 * @param map array of strings representing map
 * @param y y axis (number of lines)
 * @param x x axis (length of line)
 * @return int 1 OK, error otherwise
 */
int				is_in_bounds(char **map, size_t y, size_t x);
/** @} */

/**
 * @defgroup Utils Utils functions
 * @brief All the functions used to help the program.
 * @{
 */

/**
 * @brief Try to open the map file specified by map_name.
 *
 * @param file_name file name to open
 * @return int fd=OK, -1 if an error occurred
 */
int				safe_open(char *file_name);

/**
 * @brief Close safely the file descriptor
 * Modify the file descriptor to -1 after closing it
 *
 * @param fd pointer to the file descriptor to close
 * @return int 0 OK, -1 if an error occurred
 */
int				safe_close(int *fd);

/**
 * @brief Try to open the file specified by file_name.
 *
 * @param file_name map file name to open
 * @return int 1 OK, 0 if an error occurred
 */
int				try_to_open_close_file(char *file_name);

/**
 * @brief Count the number of strings that an array have
 * Should absolutely be NULL-Terminated
 *
 * @param array array of strings
 * @return size_t number of strings
 */
size_t			count_array_length(char **array);

/**
 * @brief Free the strings of the file
 *
 * @param map map structure
 */
void			ft_free_file(t_map *map);

/**
 * @brief Free all the textures stored in mlx structure and map struct
 *
 * @param mlx mlx structure
 * @param map map structure
 */
void			ft_free_textures(t_mlx *mlx, t_map *map);

/**
 * @brief Free the path (name) of the textures in memory
 *
 * @param map map structure
 */
void			ft_free_textures_path(t_map *map);
/** @} */

/**
 * @defgroup Print Print functions
 * @brief All the functions used to print nicely.
 * @{
 */

/** @} */

#endif
