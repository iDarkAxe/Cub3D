/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:59:08 by ppontet           #+#    #+#             */
/*   Updated: 2025/08/07 21:05:24 by ppontet          ###   ########lyon.fr   */
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

/**
 * @defgroup Events Events macro
 * @brief Regroup all the events macro used in the project
 * (originally in X.h but copied to avoid dependancy)
 * @{
 */
// # define DestroyNotify 17
// # define StructureNotifyMask (1L<<17)
// # define KeyPress 2
// # define KeyPressMask (1L<<0)
/** @} */

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
# define KEY_ESCAPE 65307
/**
 * @brief Keycode for the enter key.
 */
# define KEY_ENTER 65293
/**
 * @brief Keycode for the space key.
 */
# define KEY_SPACE 32
/**
 * @brief Keycode for the left key.
 */
# define KEY_ARROW_LEFT 65361
/**
 * @brief Keycode for the up key.
 */
# define KEY_ARROW_UP 65362
/**
 * @brief Keycode for the right key.
 */
# define KEY_ARROW_RIGHT 65363
/**
 * @brief Keycode for the down key.
 */
# define KEY_ARROW_DOWN 65364
/**
 * @brief Keycode for the A key.
 */
# define KEY_A 97
/**
 * @brief Keycode for the W key.
 */
# define KEY_W 119
/**
 * @brief Keycode for the D key.
 */
# define KEY_D 100
/**
 * @brief Keycode for the S key.
 */
# define KEY_S 115

/**
 * @brief Keycode for the C key.
 */
# define KEY_C 99

/**
 * @brief Keycode for the M key.
 */
# define KEY_M 109

/**
 * @brief Keycode for the F key.
 */
# define KEY_F 102
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
void				set_key(int keycode, t_input *input, bool set);
/**
 * @brief Toggle the input according to the keycode
 * 
 * @param[in] keycode key pressed
 * @param[out] input structure containing all inputs
 */
void				toggle_key(int keycode, t_input *input);
/** @} */

#endif
