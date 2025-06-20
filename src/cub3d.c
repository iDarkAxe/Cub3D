/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:03:55 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/20 15:29:56 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_keys.h"
#include "mlx.h"
#include "cub3d.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_print.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
	ft_free_file(&map);
	return (0);
}
