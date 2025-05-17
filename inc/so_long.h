/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:08:27 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/17 14:12:41 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/**
 * @file so_long.h
 * @brief Header file for the so_long project.
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
	int				collectibles;
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
int					so_long(int argc, char **argv);

/**
 * @brief Free the textures from the map.
 *
 * @param mlx Pointer to the mlx structure.
 * @param map Pointer to the map structure.
 */
void				free_map_textures(t_mlx *mlx, t_map *map);

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

/**
 * @brief Structure used to draw a rectangle.
 *
 */
typedef struct s_rectangle
{
	int				x;
	int				y;
	int				width;
	int				height;
	int				color;
}					t_rectangle;

/**
 * @brief Structure used to draw a circle.
 *
 */
typedef struct s_circle
{
	int				x;
	int				y;
	int				radius;
	int				color;
}					t_circle;

/**
 * @brief Function used to store the textures in the map structure.
 *
 * @param mlx Pointer to the mlx structure.
 * @param map Pointer to the map structure.
 * @return void* NULL if failed, map if success.
 */
void				*ft_store_textures(t_mlx *mlx, t_map *map);

/**
 * @brief Draw the map on the window (use it only at startup).
 *
 * @param mlx Pointer to the mlx structure.
 * @param map Pointer to the map structure.
 */
void				ft_draw_map(t_mlx *mlx, t_map *map);

/**
 * @brief Draw a tile on the window.
 *
 * @param mlx Pointer to the mlx structure.
 * @param img Image to draw.
 * @param coords Coordinates of the tile.
 */
void				ft_draw_tile(t_mlx *mlx, t_img img, t_coordinates coords);

/**
 * @brief Draw the player on the window.
 * Needs the old_player_pos to draw the previous floor tile.
 *
 * @param mlx Pointer to the mlx structure.
 * @param map Pointer to the map structure.
 * @param facing Facing direction of the player.
 * @param old_player_pos Coordinates of the previous player position.
 */
void				ft_draw_player(t_mlx *mlx, t_map *map, int facing,
						t_coordinates old_player_pos);
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
 * @brief Verify the dimensions of the map.
 * Verifies the length of each line and the number of lines,
	it should be a rectangle, and the file should be readable.
 * A rectangle has the same length for each line.
 * It should be at least 3 lines (2 for the borders, 1 for the player to move).
 *
 * @param map_name Name of the map file.
 * @return t_map_size Map dimensions and metadata.
 */
t_map_size			dimensions_verif(char *map_name);

/**
 * @brief Check the borders of the map.
 * Verifies that the map is surrounded by walls.
 *
 * @param map_size Map dimensions and metadata.
 * @return t_map* Map structure.
 */
t_map				*check_borders(t_map_size map_size);

/**
 * @brief Check the validity access of the map.
 * Create a copy of the map to check if all the collectibles
 * and the exit are accessible.
 *
 * @param map Structure contenant la carte et ses métadonnées.
 * @return int 0 si valide, -1 sinon.
 */
int					validate_map(t_map *map);

/**
 * @brief Initialize the map structure.
 *
 * @param map Pointer to the map structure.
 * @param map_size Map dimensions and metadata.
 * @return t_map* Map structure.
 */
t_map				*fill_map(t_map *map, t_map_size map_size);

/**
 * @brief Store the map in the map structure.
 *
 * @param map Pointer to the map structure.
 * @param len Map dimensions and metadata.
 */
void				free_map(t_map *map, char **map_to_delete, size_t len);
/** @} */

/**
 * @defgroup Utils Utils functions
 * @brief All the functions used to help the program.
 * @{
 */

/**
 * @brief Find the position of a character in the map.
 *
 * @param map Pointer to the map structure.
 * @param character character to find.
 * @return t_coordinates coordinates of the character.
 */
t_coordinates		find_position(t_map *map, char character);

/**
 * @brief Find the maximum number of collectibles in the map.
 *
 * @param map Pointer to the map structure.
 * @return int Number of collectibles.
 */
int					find_max_collectibles(t_map *map);

/**
 * @brief Create a copy of source into a new pointer
 *	NEEDS to be freed
 * @param source Source string.
 * @return char* Pointer to the new string.
 */
char				*ft_strdup(const char *source);
/** @} */

/**
 * @defgroup Print Print functions
 * @brief All the functions used to print nicely.
 * @{
 */

/**
 * @brief Print the position of the mouse.
 * @return ssize_t Number of moves.
 */
ssize_t				ft_print_position(int x, int y);

/**
 * @brief Print the keycode of the pressed key.
 * @return ssize_t Number of moves.
 */
ssize_t				ft_print_keycode(int keycode);

/**
 * @brief Print the color of the pixel.
 */
ssize_t				ft_print_color(int color);

/**
 * @brief Print the map in the terminal.
 * @return ssize_t Number of moves.
 */
ssize_t				ft_print_map(t_map *map, char **map_to_print);

/**
 * @brief Print the number of moves.
 * @return ssize_t Number of moves.
 */
ssize_t				ft_print_number_of_moves(size_t number_of_moves);
/** @} */

/**
 * @defgroup Random Random functions
 * @brief All the functions used to generate random numbers.
 * @{
 */

/**
 * @brief Generate a random int number.
 * @return int Random number.
 */
int					ft_random(int fd);

/**
 * @brief Initialize the random function
 * (generates the seed from a random source).
 * @return int 0 on success, -1 on failure.
 */
int					ft_random_init(void);
/** @} */

#endif
