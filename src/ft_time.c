/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:22:20 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/30 12:22:21 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>

uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (tv.tv_sec < 0 || tv.tv_usec < 0)
		return (0);
	return ((uint64_t)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	count_fps(void)
{
	static uint64_t	last_render_time = 0;
	static uint64_t	starting = 0;
	uint64_t		current_time;

	if (DEBUG_PRINT_FPS == 0)
		return ;
	if (starting == 0)
	{
		starting = get_time_ms();
		last_render_time = starting;
	}
	current_time = get_time_ms();
	if (current_time - last_render_time > 0)
	{
		if (DEBUG_PRINT_KEYCODE == 0 && DEBUG_FPS_REFRESH == 1)
			printf("\rFPS: %lu, dT: %lu", 1000 / (current_time
					- last_render_time), current_time - last_render_time);
		else
			printf("FPS: %lu, dT: %lu\n", 1000 / (current_time
					- last_render_time), current_time - last_render_time);
		last_render_time = current_time;
	}
}
