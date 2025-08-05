/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:08:27 by ppontet           #+#    #+#             */
/*   Updated: 2025/08/05 15:36:07 by rdesprez         ###   ########.fr       */
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
# include <stdint.h>
# include <unistd.h>

/**
 * @defgroup Macros Macros Functions
 * @brief Macros used in the project.
 * @{
 *
 */
# define PI 3.141592653589793238462643383279502884197169399375105820974944592307

/**
 * @brief Enable Minimap by default and can be toggled with the 'M' key.
 */
# define MINIMAP_DEFAULT_VALUE true
/**
 * @brief Enable Field of View by default and can be toggled with the 'F' key.
 */
# define FIELD_OF_VIEW_DEFAULT_VALUE true
/**
 * @brief Enable Collision by default and can be toggled with the 'C' key.
 */
# define COLLISION_DEFAULT_VALUE true

# define MINIMAP_PLAYER_COLOR 0xffffff00
# define MINIMAP_PLAYER_LINE_OF_SIGHT_COLOR 0xffffff00
# define MINIMAP_PLAYER_CONE_OF_SIGHT_COLOR 0xffffaaaa
# define MINIMAP_FLOOR_COLOR 0xff000000
# define MINIMAP_WALL_COLOR 0xffffffff
# define MINIMAP_TILE_SIZE 16
// Any size higher half of MINIMAP_TILE_SIZE will be strange
# define MINIMAP_PLAYER_SIZE 4
# define MINIMAP_LINE_OF_SIGHT_FACTOR 2

# define DEBUG_PRINT_KEYCODE 0
# define DEBUG_PRINT_FPS 0
# define DEBUG_FPS_REFRESH 0

// If you want to follow closely to the subject, you need to set these to 0
# define CROSS_APPLY_SETTINGS 0
# define ESCAPE_APPLY_SETTINGS 0

/** @} */
/**
 * @defgroup Main Main Functions
 * @brief Core functionality of the program.
 * @{
 */

/**
 * @brief Main function of the cub3d project
 *
 * @param argc number of arguments
 * @param argv array of string arguments
 * @return int 0 if the program ends correctly, -1 otherwise
 */
int					cub3d(int argc, char **argv);

/**
 * @brief Check the arguments passed to the program.
 *
 * @param argc argument count
 * @param argv array of arguments
 * @param args pointer to args struct to fill
 * @return int 1 OK, -1 if error
 */
int					check_args(int argc, char **argv, t_args *args);

/**
 * @brief Fill the config region of the file
 *
 * @param map map structure
 * @return char** NULL if error, config otherwise
 */
char				**fill_config_region(t_map *map);

/**
 * @brief Fill the map region of the file
 *
 * @param map map structure
 * @return char** NULL if error, map otherwise
 */
char				**fill_map_region(t_map *map);

/**
 * @brief Read the map file line by line and return an array of strings.
 *
 * @param map map structure to store the lines
 * @param map_name map file name to read
 * @return char** array of strings containing the map lines
 */
char				**read_file_lines(t_map *map, char *map_name);

/**
 * @brief Simple function to count the number of lines in a file.
 *
 * @param file_name file name to count lines in
 * @return size_t
 */
size_t				count_file_lines(char *file_name);

/**
 * @brief Store the textures names in the structure
 *
 * @param map map structure
 * @return char* NULL if error, OK otherwise
 */
char				*store_textures_names(t_map *map);

/**
 * @brief Exit the program.
 *
 * @param mlx Pointer to the mlx structure.
 * @param map Pointer to the map structure.
 */
void				ft_exit(t_mlx mlx, t_map *map);

/**
 * @brief Initialize the mlx structure, create settings window, and load game
 *
 * @param data data structure
 * @return int
 */
int					ft_mlx_init(t_data *data);

/**
 * @brief Close and free the mlx structure.
 *
 * @param mlx mlx structure
 */
void				ft_mlx_end(t_mlx *mlx);
/** @} */

/**
 * @defgroup Draw Draw functions
 * @brief All the functions used to draw elements on the screen.
 * @{
 */

/** @} */

/**
 * @defgroup Settings Settings functions
 * @brief All the functions used for settings.
 * @{
 */

/**
 * @brief Generate the window settings for the program.
 *
 * @param mlx mlx structure
 * @return void* win_settings_ptr if success, NULL if error
 */
void				*ft_settings(t_mlx *mlx);

enum e_screen_size	circle_state(int x, int y);
int					ft_set_screen_size(t_mlx *mlx, enum e_screen_size size);
void				ft_free_settings(t_mlx *mlx);
void				main_hooks(t_mlx *mlx);
void				settings_hooks(t_data *data);
void				state_machine(int keycode, t_mlx *mlx);
/** @} */

/**
 * @defgroup Hooks Hooks functions
 * @brief All the functions used to use hooks on windows.
 * @{
 */

int					hook_handle_mouse_motion(int x, int y, void *param);
int					hook_close_window(void *param);
int					hook_handle_keypress(int keycode, void *param);
// Settings hooks
int					hook_settings_handle_mouse_click(int button, int x, int y,
						void *param);
int					hook_settings_handle_mouse_motion(int x, int y,
						void *param);
int					hook_settings_close_window(void *param);
int					hook_settings_handle_keypress(int keycode, void *param);
/** @} */

/**
 * @defgroup Player Player functions
 * @brief All the functions used to make the player playable.
 * @{
 */

/** @} */

/**
 * @defgroup Map_verif Map verification functions
 * @brief All the functions used to verify the map.
 * @{
 */

/**
 * @brief Check the map structure and try to open the map file.
 * sets error to -1 if an error occurred.
 *
 * @param map map structure to check and initialize
 * @param map_name name of the map file.
 * @return t_map Structure containing the map dimensions and metadata.
 */
t_map				ft_map_check_dimensions(t_map *map, char *map_name);

/**
 * @brief Check if the config is properly formatted or not
 *
 * @param map map structure
 * @return t_map map structure
 */
t_map				ft_check_config(t_map *map);

/**
 * @brief Check the floor and ceiling colors
 *
 * @param map map structure
 * @return t_map map structure
 */
t_map				ft_check_floor_ceiling(t_map *map);

/**
 * @brief Return a positive number if a config line is detected
 *
 * @param line line to check
 * @return int 0 not config line, positive number otherwise
 */
size_t				is_config_line(char *line);

/**
 * @brief Check if the map has only acceptable characters
 * and if there is borders everywhere, as it should be
 *
 * @param map map structure
 * @return t_map map structure
 */
t_map				check_map_chars_borders(t_map *map);

/**
 * @brief Find the position of the player with charset in the map
 *
 * @param map map structure
 * @param charset strings of autorized characters for player
 * @return t_coordinates coordinates of player
 */
t_coordinates		find_position(t_map *map, const char *charset);

/**
 * @brief Validate if the map has unclosed holes or an unfinished outer layer
 *
 * @param map map structure
 * @return int 1 OK, error otherwise
 */
int					validate_map(t_map *map);

/**
 * @brief Check if a character is walkable or not
 *
 * @param c character
 * @return int 1 OK, error otherwise
 */
int					is_walkable(char c);

/**
 * @brief Check if a position is in bounds of map or not
 *
 * @param map array of strings representing map
 * @param y y axis (number of lines)
 * @param x x axis (length of line)
 * @return int 1 OK, error otherwise
 */
int					is_in_bounds(char **map, size_t y, size_t x);
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
int					safe_open(char *file_name);

/**
 * @brief Close safely the file descriptor
 * Modify the file descriptor to -1 after closing it
 *
 * @param fd pointer to the file descriptor to close
 * @return int 0 OK, -1 if an error occurred
 */
int					safe_close(int *fd);

/**
 * @brief Try to open the file specified by file_name.
 *
 * @param file_name map file name to open
 * @return int 1 OK, 0 if an error occurred
 */
int					try_to_open_close_file(char *file_name);

/**
 * @brief Count the number of strings that an array have
 * Should absolutely be NULL-Terminated
 *
 * @param array array of strings
 * @return size_t number of strings
 */
size_t				count_array_length(char **array);

/**
 * @brief Free all the memory allocated for the data structure.
 *
 * @param data data structure
 */
void				ft_free_all(t_data *data);

/**
 * @brief Free the strings of the file
 *
 * @param map map structure
 */
void				ft_free_file(t_map *map);

/**
 * @brief Free all the textures stored in mlx structure and map struct
 *
 * @param mlx mlx structure
 * @param map map structure
 */
void				ft_free_textures(t_mlx *mlx, t_map *map);

/**
 * @brief Free the path (name) of the textures in memory
 *
 * @param map map structure
 */
void				ft_free_textures_path(t_map *map);

/**
 * @brief Free the map structure
 *
 * @param map map structure
 */
void				ft_free_map(t_map_raoul *map);

/**
 * @brief Get the current time in milliseconds.
 * 
 * @return uint64_t 
 */
uint64_t			get_time_ms(void);

/**
 * @brief Count the FPS and print it to the console.
 * It will print the FPS every second if DEBUG_PRINT_FPS is set to 1.
 */
void				count_fps(void);
/** @} */

#endif
