/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:18:12 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/25 13:02:21 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DRAW_H
# define FT_DRAW_H

# include "data_structure.h"
# include <stdbool.h>

/**
 * @file ft_draw.h
 * @brief Header file for the draw functions.
 *
 */

typedef struct s_circle
{
	int	x;
	int	y;
	int	radius;
	int	color;
}		t_circle;

void	ft_draw_circle(t_mlx *mlx, void *win_ptr, t_circle element);
void	ft_put_circle_specific(t_mlx *mlx, void *win_settings_ptr,
			enum e_screen_size num, bool is_enabled);
void	ft_put_all_circle_to_win(t_mlx *mlx, void *win_settings_ptr,
			bool is_enabled);

#endif
