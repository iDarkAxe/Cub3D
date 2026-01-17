/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_pool_worker.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 10:21:04 by ppontet           #+#    #+#             */
/*   Updated: 2026/01/17 12:50:43 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_render.h"

static void	*cub_render_worker(void *arg);

void	cub_render_pool_init(t_render_pool *pool)
{
	size_t	i;

	pool->stop = false;
	i = 0;
	while (i < RENDER_THREADS)
	{
		pool->tasks[i].data = NULL;
		pool->tasks[i].work_available = false;
		pool->tasks[i].done = false;
		pthread_mutex_init(&pool->tasks[i].mutex, NULL);
		pthread_cond_init(&pool->tasks[i].cond, NULL);
		pthread_create(&pool->threads[i], NULL, cub_render_worker,
			&pool->tasks[i]);
		i++;
	}
	pool->initialized = 1;
}

void	cub_render_pool_destroy(t_render_pool *pool)
{
	size_t	i;

	i = 0;
	while (i < RENDER_THREADS)
	{
		pthread_mutex_lock(&pool->tasks[i].mutex);
		pool->tasks[i].data = NULL;
		pool->tasks[i].work_available = true;
		pthread_cond_signal(&pool->tasks[i].cond);
		pthread_mutex_unlock(&pool->tasks[i].mutex);
		i++;
	}
	i = 0;
	while (i < RENDER_THREADS)
	{
		pthread_join(pool->threads[i], NULL);
		pthread_mutex_destroy(&pool->tasks[i].mutex);
		pthread_cond_destroy(&pool->tasks[i].cond);
		i++;
	}
}

void	worker_finish_task(t_render_task *task)
{
	pthread_mutex_lock(&task->mutex);
	task->done = true;
	pthread_cond_signal(&task->cond);
	pthread_mutex_unlock(&task->mutex);
}

void	*cub_render_worker(void *arg)
{
	t_render_task	*task;
	int				x;

	task = (t_render_task *)arg;
	while (1)
	{
		pthread_mutex_lock(&task->mutex);
		while (!task->work_available)
			pthread_cond_wait(&task->cond, &task->mutex);
		if (task->data == NULL)
		{
			pthread_mutex_unlock(&task->mutex);
			return (NULL);
		}
		task->work_available = false;
		pthread_mutex_unlock(&task->mutex);
		x = task->x_start;
		while (x < task->x_end)
		{
			cub_render_x_column(task->data, x, &task->plane);
			x++;
		}
		worker_finish_task(task);
	}
}
