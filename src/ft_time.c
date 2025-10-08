/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:22:20 by ppontet           #+#    #+#             */
/*   Updated: 2025/10/08 16:31:46 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdbool.h>
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

uint64_t	timeval_to_us(const struct timeval *tv)
{
	if (tv == NULL)
		return (0);
	return ((uint64_t)tv->tv_sec * 1000000 + (uint64_t)tv->tv_usec);
}

void	print_fps(uint16_t fps, double delta)
{
	if (!DEBUG_PRINT_FPS)
		return ;
	if (DEBUG_PRINT_KEYCODE == 0 && DEBUG_FPS_REFRESH == 1)
		printf("\rFPS: %3hu dT: %.3f ms\033[K", fps, delta);
	else
		printf("FPS: %3hu dT: %.3f ms\n", fps, delta);
}

uint16_t	count_fps(bool print)
{
	static struct timeval	last_render_time = {0, 0};
	struct timeval			current_time;
	uint64_t				delta_us;
	double					delta_ms;
	uint16_t				fps_count;

	gettimeofday(&current_time, NULL);
	if (last_render_time.tv_sec == 0 && last_render_time.tv_usec == 0)
	{
		last_render_time = current_time;
		return (0);
	}
	delta_us = timeval_to_us(&current_time) - timeval_to_us(&last_render_time);
	if (delta_us == 0)
		return (0);
	delta_ms = (double)delta_us / 1000.0;
	fps_count = (uint16_t)(1000.0 / delta_ms);
	if (print)
		print_fps(fps_count, delta_ms);
	last_render_time = current_time;
	return (fps_count);
}
