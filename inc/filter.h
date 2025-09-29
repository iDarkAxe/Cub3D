/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:59:08 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/27 00:57:19 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILTER_H
# define FILTER_H

/**
 * @file filter.h
 * @brief Header file for filters.
 *
 */

# include "data_structure.h"

/* Constants to convert a RGB color to a grey value */
# define LUMA_RED_WEIGHT 0.299
# define LUMA_GREEN_WEIGHT 0.587
# define LUMA_BLUE_WEIGHT 0.114

/**
 * @brief Define if all the textures are modified using the same filter or not
 *
 */
# define RANDOM_FILTER_ON_ALL 0

void	add_filter(t_img *img, int filter);
void	add_filter_protected(t_img *img, int filter);
void	add_tint(t_img *img, unsigned char red_add, unsigned char green_add,
			unsigned char blue_add);
void	add_tint_protected(t_img *img, unsigned char red_add,
			unsigned char green_add, unsigned char blue_add);
void	apply_filters_on_textures(t_textures *textures);
void	filter_overflow(t_color *pixel, t_color filter);
void	swap_textures(t_map *map);
void	change_filter(t_data *data, int keycode);
void	convert_textures_to_black_and_white(t_map *map);
void	ft_free_alt_textures(t_mlx *mlx, t_map *map);

#endif
