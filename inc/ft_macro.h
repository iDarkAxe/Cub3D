/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_macro.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 14:59:36 by ppontet           #+#    #+#             */
/*   Updated: 2026/01/17 15:15:48 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MACRO_H
# define FT_MACRO_H

/**
 * @defgroup Macros Macros Functions
 * @brief Macros used in the project.
 * @{
 *
 */

/**
 * @brief PI approximation
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
/**
 * @brief Enable Filters features
 */
# define ENABLE_FILTERS true
/**
 * @brief Enable Multi-Threaded Rendering
 */
# define ENABLE_MULTI_THREAD_RENDERING 0
/**
 * @brief Number of threads for the pool
 */
# define RENDER_THREADS 4

// Playability settings
/**
 * @brief Value used to define the sensitivity of the mouse.
 * This value is multiplied by the delta mouse x to get the turn amount.
 * A higher value will make the mouse more sensitive and will turn faster.
 * Anything higher or lower than 0.001f will be strange.
 */
# define MOUSE_SENSITIVITY_FACTOR 0.001f
/**
 * @brief Value used to define the turning speed of the player.
 * This value is multiplied by the input to get the turn amount.
 * A higher value will make the player turn faster.
 */
# define MOVEMENT_SPEED_TURNING 0.015f
/**
 * @brief Value used to define the movement speed of the player 
 * in forward or backward.
 * This value is multiplied by the input to get the amount.
 * A higher value will make the player walk faster.
 */
# define MOVEMENT_SPEED_FWD_BWD 0.025f
/**
 * @brief Value used to define the movement speed of the player 
 * when moving left or right.
 * This value is multiplied by the input to get the amount.
 * A higher value will make the player walk faster.
 */
# define MOVEMENT_SPEED_LEFT_RIGHT 0.015f

// Minimap settings
# define MINIMAP_PLAYER_COLOR 0xffffff00
# define MINIMAP_PLAYER_LINE_SIGHT_COLOR 0xffffff00
# define MINIMAP_PLAYER_CONE_SIGHT_COLOR 0xffffaaaa
# define MINIMAP_FLOOR_COLOR 0xff000000
# define MINIMAP_WALL_COLOR 0xffffffff
# define MINIMAP_KEY_COLOR 0xffffff00
# define MINIMAP_DOOR_COLOR 0xff0000ff
/**
 * @brief Number of tiles on X axis
 */
# define MINIMAP_NUM_TILES_X 15
/**
 * @brief Number of tiles on Y axis
 */
# define MINIMAP_NUM_TILES_Y 15
# define MINIMAP_TILE_SIZE 16
# define MINIMAP_TILES_X 15
# define MINIMAP_TILES_Y 15
// Any size higher half of MINIMAP_TILE_SIZE will be strange
# define MINIMAP_PLAYER_SIZE 4
# define MINIMAP_LINE_OF_SIGHT_FACTOR 2
/**
 * @brief Enable Minimap FOV Zone
 */
# define MINIMAP_ENABLE_FOV_ZONE 0
/**
 * @brief Step angle division for minimap FOV zone rendering
 */
# define MINIMAP_STEP_ANGLE_DIV 20.0f
/**
 * @brief Set a maximum length to the ray in the minimap fov zone
 */
# define MINIMAP_ENABLE_MAX_RAY_LENGTH 1
# define MINIMAP_MAX_RAY_LENGTH 2.0f

// Debug printing settings
/**
 * @brief Enable to print key presses
 */
# define DEBUG_PRINT_KEYCODE 0
/**
 * @brief Enable if you want to see the FPS
 */
# define DEBUG_PRINT_FPS 1
/**
 * @brief Enable if you want to skip rendering when there is no movement
 */
# define SKIP_NO_MVMT 1
/**
 * @brief Enable to keep the FPS counter on a single line
 * @warning if you use it with any of the other DEBUG, the output is undefined
 * 
 */
# define DEBUG_FPS_REFRESH 0
/**
 * @brief Enable printing of message to indicate texture swapping
 */
# define DEBUG_PRINT_TEXTURE_SWAP 0
/**
 * @brief Enable printing message when a texture is altered with filters
 */
# define DEBUG_PRINT_TEXTURE_ALTERED 0

// If you want to follow closely to the subject, you need to set these to 0
/**
 * @brief Enable if closing the settings window should behave as 'Enter'
 */
# define CROSS_APPLY_SETTINGS 0
/**
 * @brief Enable pressing Esc in the settings menu should behave as 'Enter'
 */
# define ESCAPE_APPLY_SETTINGS 0
/** @} */

#endif // FT_MACRO_H
