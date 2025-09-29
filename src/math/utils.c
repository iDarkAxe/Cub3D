/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:00:59 by rdesprez          #+#    #+#             */
/*   Updated: 2025/09/11 14:05:05 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	absf(float n)
{
	if (n < 0.f)
		return (-n);
	return (n);
}

int	abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

double	mind(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}
