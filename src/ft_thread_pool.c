/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_pool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 10:21:04 by ppontet           #+#    #+#             */
/*   Updated: 2026/01/17 12:47:39 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_thread_pool(t_data *data, t_vec2 plane)
{
	size_t	i;
	int		x;
	int		cols_per_thread;

	i = 0;
	x = 0;
	cols_per_thread = data->mlx.win_size.x / RENDER_THREADS;
	while (i < RENDER_THREADS)
	{
		pthread_mutex_lock(&data->pool.tasks[i].mutex);
		data->pool.tasks[i].data = data;
		data->pool.tasks[i].plane = plane;
		data->pool.tasks[i].x_start = x;
		if (i == RENDER_THREADS - 1)
			data->pool.tasks[i].x_end = data->mlx.win_size.x;
		else
			data->pool.tasks[i].x_end = x + cols_per_thread;
		data->pool.tasks[i].done = false;
		data->pool.tasks[i].work_available = true;
		pthread_cond_signal(&data->pool.tasks[i].cond);
		pthread_mutex_unlock(&data->pool.tasks[i].mutex);
		x = data->pool.tasks[i].x_end;
		i++;
	}
}

void	wait_thread_pool(t_render_pool *pool)
{
	size_t	i;

	i = 0;
	while (i < RENDER_THREADS)
	{
		pthread_mutex_lock(&pool->tasks[i].mutex);
		while (!pool->tasks[i].done)
			pthread_cond_wait(&pool->tasks[i].cond,
				&pool->tasks[i].mutex);
		pthread_mutex_unlock(&pool->tasks[i].mutex);
		i++;
	}
}
