/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:50:35 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/17 16:42:48 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub3d_raoul(int argc, char **argv);

/**
 * @brief Main function of the program.
 * Calls only the cub3d function.
 *
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 * @return int Return values of the cub3d function.
 */
// int	main(int argc, char **argv)
// {
// 	return (cub3d(argc, argv));
// }

int	main(int argc, char **argv)
{
	return (cub3d_raoul(argc, argv));
}
