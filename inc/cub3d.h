/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:08:27 by ppontet           #+#    #+#             */
/*   Updated: 2026/01/17 15:00:12 by ppontet          ###   ########lyon.fr   */
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
# include "ft_macro.h"
# include <stddef.h>
# include <stdint.h>
# include <unistd.h>
# include <sys/time.h>

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
 * @brief Reads and verifies the arguments passed to the program
 *
 * @param argc argument count
 * @param argv array of arguments
 * @param args pointer to args struct to fill
 * @return int 1 OK, -1 otherwise with side effect of printing error
 */
int					cub_read_args(int argc, char **argv, t_args *args);

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
/**
 * @brief Return an enum according to selected circle using coordinates
 * 
 * @param[in] x x axis 
 * @param[in] y y axis 
 * @return enum e_screen_size state
 */
enum e_screen_size	circle_state(int x, int y);
/**
 * @brief Set screen size according to an enum
 * 
 * @param[in,out] mlx mlx structure
 * @param[in] size enum representing the size of the screen selected 
 * @return int 
 */
int					ft_set_screen_size(t_mlx *mlx, enum e_screen_size size);
/**
 * @brief Free all the settings variables
 * 
 * @param[in,out] mlx mlx structure 
 */
void				ft_free_settings(t_mlx *mlx);
/**
 * @brief Set the settings hooks on the settings window
 * 
 * @param[in,out] data data structure
 */
void				settings_hooks(t_data *data);
/**
 * @brief State machine for the settings window.
 *
 * @param[in] keycode keycode of the key pressed
 * @param[in,out] mlx Pointer to the mlx structure
 */
void				state_machine(int keycode, t_mlx *mlx);
/** @} */

/**
 * @defgroup Hooks Hooks functions
 * @brief All the functions used to use hooks on windows.
 * @{
 */

/**
 * @brief Hook when a key is pressed
 * 
 * @param[in] keycode keycode of key pressed
 * @param[in,out] param param 
 * @return int keycode
 */
int					cub_keydown_hook(int keycode, void *param);
/**
 * @brief Hook when a key is released
 * 
 * @param[in] keycode keycode of key released
 * @param[in,out] param param 
 * @return int keycode
 */
int					cub_keyup_hook(int keycode, void *param);
/**
 * @brief Hook when the mouse is moved while clicking
 * 
 * @param[in] button button pressed
 * @param[in] x x axis 
 * @param[in] y y axis 
 * @param[in,out] param param
 * @return int 0 always
 */
int					cub_mouse_click_hook(int button, int x, int y, void *param);
/**
 * @brief Hook when the mouse is moved
 * 
 * @param[in] x x axis 
 * @param[in] y y axis 
 * @param[in,out] param param
 * @return int 0 always
 */
int					cub_mouse_hook(int x, int y, void *param);
// Settings hooks
/**
 * @brief Hook when the mouse is moved while clicking for the settings
 * 
 * @param[in] button button pressed
 * @param[in] x x axis 
 * @param[in] y y axis 
 * @param[in,out] param param
 * @return int 0 OK, -1 otherwise
 */
int					hook_settings_handle_mouse_click(int button, int x, int y,
						void *param);
/**
 * @brief Hook when the mouse is moved for the settings
 * 
 * @param[in] x x axis 
 * @param[in] y y axis 
 * @param[in,out] param param
 * @return int 0 OK, -1 otherwise
 */
int					hook_settings_handle_mouse_motion(int x, int y,
						void *param);
/**
 * @brief Hook used to close window or set the window size if MACRO Enabled
 * 
 * @param[in,out] param param
 * @return int 0 always
 */
int					hook_settings_close_window(void *param);

/**
 * @brief Handle mouse click in the settings window.
 *
 * @param[in] keycode keycode of the key pressed
 * @param[in,out] param Pointer to the mlx structure
 * @return int
 */
int					hook_settings_handle_keypress(int keycode, void *param);
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
 * @brief Check if the string contains only whitespace characters
 *
 * @param[in] str string to check
 * @return bool 1 all whitespace, 0 otherwise
 */
bool				is_only_whitespace(const char *str);

/**
 * @brief Suppress newlines in the given lines
 *
 * @param[in,out] lines Array of strings to modify
 */
void				suppress_newlines(char **lines);

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
 * @param textures textures structure
 */
void				ft_free_textures(t_mlx *mlx, t_textures *textures);

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
 * @brief Destroy the thread poool structure
 * 
 * @param[in,out] pool thread pool
 */
void				cub_render_pool_destroy(t_render_pool *pool);

/**
 * @brief Get time in milliseconds.
 * 
 * @return uint64_t milliseconds
 */
uint64_t			get_time_ms(void);

/**
 * @brief Convert a timeval in microseconds.
 * 
 * @return uint64_t microseconds
 */
uint64_t			timeval_to_us(const struct timeval *tv);

/**
 * @brief Count the FPS and print it to the console.
 * It will print the FPS every second if DEBUG_PRINT_FPS is set to 1.
 * @param print 1 to print the FPS, 0 otherwise
 * @return uint16_t the current FPS
 */
uint16_t			count_fps(bool print);
/** @} */

#endif
