/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:59:08 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/14 14:33:26 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_KEYS_H
# define FT_KEYS_H

/**
 * @file ft_keys.h
 * @brief Header file for the key used in cube3d.
 *
*/

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
# define KEY_LEFT 65361
/**
* @brief Keycode for the up key.
*/
# define KEY_UP 65362
/**
* @brief Keycode for the right key.
*/
# define KEY_RIGHT 65363
/**
* @brief Keycode for the down key.
*/
# define KEY_DOWN 65364
/**
 * @brief Keycode for the A key.
 */
# define KEY_A 97
/** @} */

#endif
