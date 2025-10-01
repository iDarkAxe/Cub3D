/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:02:10 by rdesprez          #+#    #+#             */
/*   Updated: 2025/09/30 17:44:35 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"
#include "ft_print.h"
#include "libft.h"
#include <stddef.h>

/**
 * @brief Check that the string is correctly formatted as number x number
 * 
 * @param[in] gen string containing parameters for maze gen
 * @return int 1 valid, 0 invalid
 */
static int	is_valid_size(const char *gen)
{
	const char	*pointer;
	int			start_of_second_nbr;

	pointer = gen;
	if (!pointer || !ft_isdigit(*pointer))
		return (0);
	while (ft_isdigit(*pointer))
		pointer++;
	if (*pointer != 'x')
		return (0);
	pointer++;
	start_of_second_nbr = pointer - gen;
	if (!ft_isdigit(*pointer))
		return (0);
	while (ft_isdigit(*pointer))
		pointer++;
	if (*pointer != '\0')
		return (0);
	return (start_of_second_nbr);
}

static int	error(int err)
{
	print_maze_error(err);
	return (0);
}

int	cub_parse_generation_arg(char *gen, size_t *width, size_t *height)
{
	int	w;
	int	h;
	int	start_of_second_nbr;

	start_of_second_nbr = is_valid_size(gen);
	if (start_of_second_nbr == 0)
		return (error(MAZE_ARGS_BAD_FORMAT));
	w = ft_atoi(gen);
	h = ft_atoi(&gen[start_of_second_nbr]);
	if (w <= 0 || h <= 0)
		return (error(MAZE_SIZE_NEGATIVE_VALUE));
	if (w >= MAZE_MAX_SIZE || h >= MAZE_MAX_SIZE)
		return (error(MAZE_SIZE_TOO_BIG));
	if (w < MAZE_MIN_SIZE || h < MAZE_MIN_SIZE)
		return (error(MAZE_SIZE_TOO_SMALL));
	*width = w;
	*height = h;
	return (1);
}
