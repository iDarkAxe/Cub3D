/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 18:27:14 by ppontet           #+#    #+#             */
/*   Updated: 2025/10/11 18:30:09 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

void	suppress_newlines(char **lines)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == '\n')
				lines[i][j] = 0;
			j++;
		}
		i++;
	}
}

bool	is_only_whitespace(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (false);
	while (str[i])
	{
		if (!ft_isspace((unsigned char)str[i]))
			return (false);
		i++;
	}
	return (true);
}
