/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:18:12 by ppontet           #+#    #+#             */
/*   Updated: 2025/12/16 19:07:43 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DRAW_H
# define FT_DRAW_H

/**
 * @file ft_draw.h
 * @brief Header file for the draw functions.
 *
 */

# include "data_structure.h"
# include <stdbool.h>

typedef struct s_circle	t_circle;

/**
 * @brief Structure used to store circle informations
 */
struct s_circle
{
	int	x;
	int	y;
	int	radius;
	int	color;
};

/**
 * @brief Should only be used for images with 32 bits per pixel. (standard)
 * It will result as undefined behavior if used on images with other bit depths.
 * it's because of alignment issues with the pixel data.
 *
 * @param[in,out] img image structure
 * @param[in] x x axis
 * @param[in] y y axis
 * @param[in] color color
 */
void	ft_put_pixel_to_img(t_img *img, int x, int y, int color);
/**
 * @brief Special case for 24 bits per pixel images.
 *
 * @param[in,out] img image structure
 * @param[in] x x axis
 * @param[in] y y axis
 * @param[in] color color
 */
void	ft_put_pixel_to_img_24bp(t_img *img, int x, int y, int color);

/**
 * @brief Put ON circle if is_enabled, put OFF circle if not
 * 
 * @param[in,out] mlx mlx structure
 * @param[in,out] win_ptr window pointer
 * @param[in] element element
 * @param[in] is_enabled true is ON, false is OFF
 */
void	ft_put_circle_to_win(t_mlx *mlx, void *win_ptr, t_circle element,
			bool is_enabled);
/**
 * @brief Function to put the specific case of circles defined by the enum
 * 
 * @param[in,out] mlx mlx structure
 * @param[in,out] win_settings_ptr settings window pointer
 * @param[in,out] num state to put
 * @param[in] is_enabled true is ON, false is OFF
 */
void	ft_put_circle_specific(t_mlx *mlx, void *win_settings_ptr,
			enum e_screen_size num, bool is_enabled);
/**
 * @brief Function to pull all the circle to the window following their state
 * 
 * @param[in,out] mlx  mlx structure
 * @param[in,out] win_settings_ptr settings window pointer
 * @param[in] is_enabled true is ON, false is OFF
 */
void	ft_put_all_circle_to_win(t_mlx *mlx, void *win_settings_ptr,
			bool is_enabled);

#endif
