/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:53:09 by ppontet           #+#    #+#             */
/*   Updated: 2025/10/11 18:25:27 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "data_structure.h"
#include "ft_print.h"
#include "ft_printf.h"
#include "maze.h"

void	print_map_error(t_map *map, enum e_map_error error)
{
	if (!map)
		return ;
	map->error = 1;
	ft_free_file(map);
	if (error == CONFIG_TOO_MANY_PARAMETERS)
		ft_dprintf(2,
			RED "Error" RESET "\nConfig should have only 6 parameters\n");
	else if (error == CONFIG_ALREADY_STORED)
		ft_dprintf(2,
			RED "Error" RESET "\nConfig member is already filled in\n");
	else if (error == CONFIG_MISSING_PARAMETERS)
		ft_dprintf(2,
			RED "Error" RESET "\nAt least one parameter is missing\n");
	else
		ft_dprintf(2, RED "Error" RESET "\nUnknown map error\n");
}

int	print_map_validate_error(t_map *map, enum e_map_error error)
{
	if (!map)
		return (1);
	map->error = 1;
	ft_free_file(map);
	if (error == CONFIG_MAP_TOO_SOON)
		ft_dprintf(2, RED "Error" RESET
			"\nMap lines found before all configuration parameters are set\n");
	else if (error == CONFIG_FOUND_AFTER_MAP)
		ft_dprintf(2, RED "Error" RESET
			"\nConfiguration line found after map started\n");
	else
		print_map_error(map, error);
	return (1);
}

void	print_maze_error(enum e_maze_error error)
{
	if (error == MAZE_SIZE_TOO_BIG)
		ft_dprintf(2, RED "Error" RESET
			"\nInvalid size. Width and height must be smaller than %u.\n",
			MAZE_MAX_SIZE);
	else if (error == MAZE_SIZE_TOO_SMALL)
		ft_dprintf(2, RED "Error" RESET
			"\nInvalid size. Width and height must be bigger than %u\n",
			MAZE_MIN_SIZE);
	else if (error == MAZE_SIZE_NEGATIVE_VALUE)
		ft_dprintf(2, RED "Error" RESET
			"\nInvalid size. Both dimensions must be at least 1 in size.\n");
	else if (error == MAZE_ARGS_BAD_FORMAT)
		ft_dprintf(2, RED "Error" RESET
			"\nInvalid size. Must be formatted as <width>x<height>\n");
}

int	print_error(t_map *map, enum e_fx_error error)
{
	if (!map)
		return (2);
	if (error == CHECK_ARGS)
		ft_dprintf(2, RED "Error" RESET "\nAt check_args\n");
	else if (error == FT_MAP_CHECK)
		ft_dprintf(2, RED "Error" RESET "\nAt ft_map_check_dimensions\n");
	else if (error == CONFIG_ERROR)
		ft_dprintf(2, RED "Error" RESET "\nAt ft_check_config\n");
	else if (error == STORE_TEXTURES_IMG)
		ft_dprintf(2, RED "Error" RESET "\nAt store_textures_mlx\n");
	else if (error == FT_SETTINGS)
		ft_dprintf(2, RED "Error" RESET "\nAt ft_settings\n");
	else if (error == CUB_INIT_RENDER)
		ft_dprintf(2, RED "Error" RESET "\nAt cub_init_render\n");
	else if (error == CUB_INIT)
		ft_dprintf(2, RED "Error" RESET "\nAt cub_init\n");
	else
		ft_dprintf(2, RED "Error" RESET "\nUnknown error\n");
	if (error != FT_MAP_CHECK)
		ft_free_file(map);
	if (error == CONFIG_ERROR)
		ft_free_textures_path(map);
	return (1);
}

void	print_leak_map(char **map, size_t y, size_t x)
{
	size_t	index;

	if (!map || y >= count_array_length(map) || x >= ft_strlen(map[y]))
	{
		ft_dprintf(2,
			RED "Error\n" RESET
			"invalid access: y=%u, x=%u are out of bounds\n", (unsigned int)y,
			(unsigned int)x);
		return ;
	}
	ft_printf("Character " RED "'%c'" RESET " in x=%u y=%u is invalid\n",
		map[y][x], (unsigned int)y, (unsigned int)x);
	index = 0;
	while (index++ < y - 1 && map[index])
		ft_printf("%s", map[index]);
	ft_printf(RED "%s" RESET, map[y]);
	index = 0;
	while (index++ < x)
		ft_printf(" ");
	ft_printf("↑ here\n");
	index = y + 1;
	while (map[index])
		ft_printf("%s", map[index++]);
	ft_printf("\n");
}
