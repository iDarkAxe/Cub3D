/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:33:31 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/20 18:03:44 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H

/**
 * @file ft_print.h
 * @brief Header file for the print functions.
 *
 */

# include "cub3d.h"
# include <unistd.h>

/**
 * @defgroup PRINT_MACROS Print macros functions
 * @brief Print macros used to print.
 * @{
 */
# define RESET "\033[0m"
# define RESET_COLOR RESET
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
/** @} */

/**
 * @defgroup ERROR_TYPES Error types
 * @brief Error types
 * @{
 */
enum							e_map_error
{
	CONFIG_TOO_MANY_PARAMETERS,
	CONFIG_ALREADY_STORED,
	CONFIG_MISSING_PARAMETERS
};

enum							e_fx_error
{
	FT_MAP_CHECK,
	CHECK_ARGS,
	CONFIG_ERROR
};
/** @} */

/**
 * @defgroup Print Print functions
 * @brief All the functions used to print.
 * @{
 */
ssize_t	ft_print_position(int x, int y);
ssize_t	ft_print_file(t_map *map);
ssize_t	ft_print_config(t_map *map);
ssize_t	ft_print_map(t_map *map);
ssize_t	ft_print_floor_ceiling(t_map *map);
// ERRORS
void	print_map_error(t_map *map, enum e_map_error error);
int		print_error(t_map *map, enum e_fx_error error);
/** @} */

#endif
