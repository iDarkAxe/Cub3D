/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:36:23 by rdesprez          #+#    #+#             */
/*   Updated: 2025/08/07 15:59:53 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "maze.h"

static unsigned long	edit_random_state(int set, unsigned int seed)
{
	static unsigned long	random = 0;
	static const int		double_rand_max = FT_RAND_MAX * 2;

	if (set)
	{
		random = seed;
		return (0);
	}
	else
	{
		random = random * 1103515245 + 12345;
		return ((unsigned int)random / double_rand_max % FT_RAND_MAX);
	}
}

void	ft_srand(unsigned int seed)
{
	edit_random_state(1, seed);
}

unsigned int	ft_rand(void)
{
	return (edit_random_state(0, 0));
}

// Simple Fisher-Yates shuffle
void	array_shuffle(int *arr, int len)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < len)
	{
		j = ft_rand() % len;
		tmp = arr[i];
		arr[i] = arr[j];
		arr[j] = tmp;
		i++;
	}
}
