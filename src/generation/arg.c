/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:02:10 by rdesprez          #+#    #+#             */
/*   Updated: 2025/08/09 11:10:15 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>

/**
 * @brief Check that the string is correctly formatted as numbers x numbers
 * 
 * @param[in] gen 
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

int	cub_parse_generation_arg(char *gen, size_t *width, size_t *height)
{
	int	w;
	int	h;
	int	start_of_second_nbr;

	start_of_second_nbr = is_valid_size(gen);
	if (start_of_second_nbr == 0)
	{
		ft_dprintf(2, RED "Error" RESET
			"\nInvalid size. Must be formatted as <width>x<height>\n");
		return (0);
	}
	w = ft_atoi(gen);
	h = ft_atoi(&gen[start_of_second_nbr]);
	if (w <= 0 || h <= 0)
	{
		ft_dprintf(2, RED "Error" RESET
			"\nInvalid size. Both dimensions must be at least 1 in size.\n");
		return (0);
	}
	*width = w;
	*height = h;
	return (1);
}
