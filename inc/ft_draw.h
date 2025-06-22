/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:18:12 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/22 18:20:16 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DRAW_H
# define FT_DRAW_H

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

void	ft_draw_circle(void *mlx_ptr, void *win_ptr, t_circle element);
void	ft_draw_all_circle(void *mlx_ptr, void *win_settings_ptr, int num);

#endif