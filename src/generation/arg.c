/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:02:10 by rdesprez          #+#    #+#             */
/*   Updated: 2025/08/05 18:24:56 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"
#include "ft_printf.h"
#include "libft.h"
#include <stddef.h>

static int	is_valid_size(char *gen)
{
	while (*gen && *gen != 'x')
		gen++;
	if (*gen != 'x')
		return (0);
	gen++;
	return (*gen);
}

int	cub_parse_generation_arg(char *gen, size_t *width, size_t *height)
{
	int	w;
	int	h;

	if (!is_valid_size(gen))
	{
		ft_dprintf(2, RED "Error" RESET
			"\nInvalid size. Must be formatted as <width>x<height>\n");
		return (0);
	}
	w = ft_atoi(gen);
	h = ft_atoi(ft_strchr(gen, 'x') + 1);
	*width = w;
	*height = h;
	return (1);
}
