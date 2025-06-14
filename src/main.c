/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:33:52 by ppontet           #+#    #+#             */
/*   Updated: 2025/06/14 14:33:26 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/**
 * @brief Main function of the program.
 * Calls only the cube3d function.
 *
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 * @return int Return values of the cube3d function.
 */
int	main(int argc, char **argv)
{
	return (cube3d(argc, argv));
}
