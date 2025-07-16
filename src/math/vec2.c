/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdesprez <rdesprez@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:38:30 by rdesprez          #+#    #+#             */
/*   Updated: 2025/06/22 18:42:07 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubtest.h"
#include <math.h>

t_vec2	vec2rotate(t_vec2 vec, float angle)
{
	t_vec2	res;

	res.x = vec.x * cos(angle) - sin(angle) * vec.y;
	res.y = vec.x * sin(angle) + cos(angle) * vec.y;
	return (res);
}
