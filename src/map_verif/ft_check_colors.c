/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:05:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/12/18 10:57:08 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>

static int				has_line_an_error(t_map *map, char **array,
							const char *line);
static unsigned char	safe_atoi(char *str, int *error, unsigned char flag);
static int				change_color_values(t_color *color, char **split,
							int *error);
static int				are_all_chars_digits(char *str);

/**
 * @brief Check that all chars in a string are digits or newline
 * 
 * @param[in] str  string to check
 * @return int 1 all digits, 0 otherwise
 */
int	are_all_chars_digits(char *str)
{
	size_t	index;

	if (!str || str[0] == '\n' || str[0] == '\0')
		return (0);
	index = 0;
	while (str[index])
	{
		if ((str[index] < '0' || str[index] > '9') && str[index] != '\n')
		{
			ft_dprintf(2, RED "Error" RESET "\nColor contains invalid char: "
				"'%c'\n", str[index]);
			return (0);
		}
		index++;
	}
	return (1);
}

unsigned char	safe_atoi(char *str, int *error, unsigned char flag)
{
	int	value;

	if (are_all_chars_digits(str) != 1)
	{
		if (error)
			*error = (1 << flag) + *error;
		return (0);
	}
	value = ft_atoi(str);
	if (value < 0 || value > 255)
	{
		ft_dprintf(2, RED "Error" RESET "\nColor out of range: %d\n", value);
		ft_dprintf(2, "Should be 0-255\n");
		if (error)
			*error = (1 << flag) + *error;
	}
	return ((unsigned char)value);
}

int	change_color_values(t_color *color, char **split, int *error)
{
	if (!color || !split || !split[0] || !split[1] || !split[2] || !error)
	{
		ft_dprintf(2, RED "Error" RESET "\nInvalid color values\n");
		return (1);
	}
	color->red = safe_atoi(split[0], error, 0);
	color->green = safe_atoi(split[1], error, 1);
	color->blue = safe_atoi(split[2], error, 2);
	if (*error != 0)
	{
		if (*error & 1)
			ft_dprintf(2, RED "Error" RESET "\nRed color is invalid\n");
		if (*error & 2)
			ft_dprintf(2, RED "Error" RESET "\nGreen color is invalid\n");
		if (*error & 4)
			ft_dprintf(2, RED "Error" RESET "\nBlue color is invalid\n");
		return (1);
	}
	return (0);
}

t_map	ft_check_floor_ceiling(t_map *map)
{
	char	**split;

	if (!map)
		return ((t_map){.error = -1});
	split = ft_split(&map->config[4][2], ',');
	if (has_line_an_error(map, split, "floor") == 1)
		return (*map);
	change_color_values(&map->textures.floor, split, &map->error);
	ft_free_array(split);
	if (map->error != 0)
		return (*map);
	split = ft_split(&map->config[5][2], ',');
	if (has_line_an_error(map, split, "ceiling") == 1)
		return (*map);
	change_color_values(&map->textures.ceiling, split, &map->error);
	ft_free_array(split);
	map->textures.ceiling.alpha = 0xff;
	map->textures.floor.alpha = 0xff;
	return (*map);
}

/**
 * @brief Check if a line has an error
 * the split shouldn't contain more than 3 strings
 *
 * @param map map structure
 * @param array array of strings
 * @param line line to check
 * @return int 1 has an error, 0 otherwse
 */
int	has_line_an_error(t_map *map, char **array, const char *line)
{
	if (!map || map->error != 0)
	{
		if (array)
			ft_free_array(array);
		return (1);
	}
	if (array && array[0] && array[1] && array[2] && array[3])
	{
		ft_dprintf(2, RED "Error" RESET
			"\nColor of %s has too many parameters\n", line);
		ft_free_array(array);
		map->error = 1;
		return (1);
	}
	if (!array || !array[0] || !array[1] || !array[2])
	{
		ft_dprintf(2, RED "Error" RESET
			"\nColor of %s has too few parameters\n", line);
		ft_free_array(array);
		map->error = 1;
		return (1);
	}
	return (0);
}
