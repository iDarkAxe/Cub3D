/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/21 13:24:27 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "ft_print.h"

// TODO SHOULD BE IN .h
char	*store_textures_names(t_map *map);
void	ft_free_textures(t_mlx *mlx, t_map *map);
void	ft_free_textures_path(t_map *map);

/**
 * @brief Main function of the cub3d project
 *
 * @param argc number of arguments
 * @param argv array of string arguments
 * @return int 0 if the program ends correctly, -1 otherwise
 */
int	cub3d(int argc, char **argv)
{
	t_map	map;
	t_mlx	mlx;

	(void)mlx;
	if (check_args(argc, argv) != 1)
		return (print_error(&map, FT_MAP_CHECK));
	map = ft_map_check(&map, argv[1]);
	if (map.error != 0)
		return (print_error(&map, CHECK_ARGS));
	map = ft_check_config(&map);
	if (map.error != 0)
		return (print_error(&map, CONFIG_ERROR));
	if (store_textures_names(&map) == NULL)
		return (print_error(&map, STORE_TEXTURES_NAMES));
	ft_free_textures_path(&map);
	ft_free_file(&map);
	return (0);
}
