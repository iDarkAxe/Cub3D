/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:59:08 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/27 00:58:16 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_KEYS_H
# define FT_KEYS_H

/**
 * @file ft_keys.h
 * @brief Header file for the key used in cub3d.
 *
 */

# include <stdbool.h>
# include "MLX42/MLX42.h"

/**
 * @defgroup Keys Keys macros
 * @brief Regroup all the keys used in the project.
 * @{
 */

/**
 * @brief Structure used to define the type of movement with directions
 */
enum	e_movement
{
	MV_UP,
	MV_LEFT,
	MV_RIGHT,
	MV_DOWN
};

/**
 * @brief Keycode for the escape key.
 */
# define KEY_ESCAPE MLX_KEY_ESCAPE
/**
 * @brief Keycode for the enter key.
 */
# define KEY_ENTER MLX_KEY_ENTER
/**
 * @brief Keycode for the space key.
 */
# define KEY_SPACE MLX_KEY_SPACE
/**
 * @brief Keycode for the left key.
 */
# define KEY_ARROW_LEFT MLX_KEY_LEFT
/**
 * @brief Keycode for the up key.
 */
# define KEY_ARROW_UP MLX_KEY_UP
/**
 * @brief Keycode for the right key.
 */
# define KEY_ARROW_RIGHT MLX_KEY_RIGHT
/**
 * @brief Keycode for the down key.
 */
# define KEY_ARROW_DOWN MLX_KEY_DOWN
/**
 * @brief Keycode for the A key.
 */
# define KEY_A MLX_KEY_A
/**
 * @brief Keycode for the W key.
 */
# define KEY_W MLX_KEY_W
/**
 * @brief Keycode for the D key.
 */
# define KEY_D MLX_KEY_D
/**
 * @brief Keycode for the S key.
 */
# define KEY_S MLX_KEY_S

/**
 * @brief Keycode for the C key.
 */
# define KEY_C MLX_KEY_C

/**
 * @brief Keycode for the M key.
 */
# define KEY_M MLX_KEY_M

/**
 * @brief Keycode for the F key.
 */
# define KEY_F MLX_KEY_F
/**
 * @brief Keycode for the V key.
 */
# define KEY_V MLX_KEY_V
/**
 * @brief Keycode for the X key.
 */
# define KEY_X MLX_KEY_X
/** @} */

/**
 * @defgroup Key Key functions
 * @brief All the functions used to manage key inputs.
 * @{
 */

/**
 * @brief Check if a keycode is a movement key
 *
 * @param[in] expected expected key
 * @param[in] keycode key pressed
 * @return true is_mv_key
 * @return false isn't
 */
bool				is_mv_key(enum e_movement expected, int keycode);
/**
 * @brief Set the input according to the keycode and the set value
 *
 * @param[in] keycode key pressed
 * @param[out] input structure containing all inputs
 * @param[in] set value to set
 */
void			set_key(int keycode, t_input *input, bool set);
/**
 * @brief Toggle the input according to the keycode
 *
 * @param[in] keycode key pressed
 * @param[out] input structure containing all inputs
 */
void			toggle_key(int keycode, t_input *input);
/**
 * @brief Change the FOV according to the keycode
 *
 * @param[in,out] data data structure
 * @param[in] keycode key pressed
 */
void			change_fov(t_data *data, int keycode);
/** @} */

#endif
