/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:36:23 by rdesprez          #+#    #+#             */
/*   Updated: 2025/08/06 11:45:00 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static unsigned long	*random_state(void)
{
	static unsigned long	random = 0;

	return (&random);
}

void	ft_srand(unsigned int seed)
{
	*random_state() = seed;
}

unsigned int	ft_rand(void)
{
	unsigned long	*state;

	state = random_state();
	*state = *state * 1103515242 + 12345;
	return ((unsigned int)(*state / 65536) % 32768);
}
