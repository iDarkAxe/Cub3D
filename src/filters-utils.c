/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/09/03 17:04:22 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structure.h"
#include "maze.h"
#include "filter.h"

void	filter_overflow(t_color *pixel, t_color filter)
{
	if (pixel->red + filter.red > 255)
		pixel->red = 255;
	else
		pixel->red = pixel->red + filter.red;
	if (pixel->blue + filter.blue > 255)
		pixel->blue = 255;
	else
		pixel->blue = pixel->blue + filter.blue;
	if (pixel->green + filter.green > 255)
		pixel->green = 255;
	else
		pixel->green = pixel->green + filter.green;
}

void	apply_filters_on_textures(t_textures *textures)
{
	int	temp;

	if (RANDOM_FILTER_ON_ALL == 0)
	{
		temp = ft_rand();
		temp = -temp & 0xEEEEEEEE;
		add_filter(&textures->north, temp);
		add_filter(&textures->south, temp);
		add_filter(&textures->east, temp);
		add_filter(&textures->west, temp);
	}
	else
	{
		add_filter(&textures->north, -ft_rand() & 0xEEEEEEEE);
		add_filter(&textures->south, -ft_rand() & 0xEEEEEEEE);
		add_filter(&textures->east, -ft_rand() & 0xEEEEEEEE);
		add_filter(&textures->west, -ft_rand() & 0xEEEEEEEE);
	}
}
