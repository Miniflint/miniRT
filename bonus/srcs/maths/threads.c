#include "miniRT.h"

// all->canvas.pixel_values

unsigned long	get_time_diff(struct timeval *last)
{
	struct timeval	now;
	unsigned long	ret;

	gettimeofday(&now, NULL);
	ret = (now.tv_sec - last->tv_sec) * 1000000UL
		+ (now.tv_usec - last->tv_usec);
	*last = now;
	return (ret);
}

t_thread_mode	get_thread_mode(t_all *all, t_threads *thread)
{
	pthread_mutex_lock(&all->mutex);
	if (thread->mode != all->thread_mode)
	{
		--all->thread_states[thread->mode];
		thread->mode = all->thread_mode;
		++all->thread_states[thread->mode];
		// if (thread->mode == (t_thread_mode)PAUSE)
		// 	printf("thread %p in PAUSE mode\n", thread);
		// else if (thread->mode == (t_thread_mode)CONTINUE)
		// 	printf("thread %p in CONTINUE mode\n", thread);
		// else if (thread->mode == (t_thread_mode)STOP)
		// 	printf("thread %p in STOP mode\n", thread);
		// else if (thread->mode == (t_thread_mode)RESET)
		// 	printf("thread %p in RESET mode\n", thread);
		// fflush(stdout);
	}
	pthread_mutex_unlock(&all->mutex);
	return (thread->mode);
}

t_thread_mode	get_thread_mode_pause(t_all *all, t_threads *thread)
{
	while (get_thread_mode(all, thread) == (t_thread_mode)PAUSE)
		usleep(200);
	return (thread->mode);
}

t_thread_mode	get_thread_mode_pause_reset(t_all *all, t_threads *thread)
{
	while (get_thread_mode(all, thread) == (t_thread_mode)PAUSE || thread->mode == (t_thread_mode)RESET)
		usleep(200);
	return (thread->mode);
}

t_thread_mode	get_thread_mode_pause_continue(t_all *all, t_threads *thread)
{
	while (get_thread_mode(all, thread) == (t_thread_mode)PAUSE || thread->mode == (t_thread_mode)CONTINUE)
		usleep(200);
	return (thread->mode);
}

void	*thread_routine(void *content)
{
	t_all		*all;
	t_threads	*thread;

	thread = content;
	all = thread->all;
	// if (thread->mode == (t_thread_mode)PAUSE)
	// 	printf("thread %p in PAUSE mode\n", thread);
	// else if (thread->mode == (t_thread_mode)CONTINUE)
	// 	printf("thread %p in CONTINUE mode\n", thread);
	// else if (thread->mode == (t_thread_mode)STOP)
	// 	printf("thread %p in STOP mode\n", thread);
	// else if (thread->mode == (t_thread_mode)RESET)
	// 	printf("thread %p in RESET mode\n", thread);
	// fflush(stdout);
	while (1)
	{
		if (get_thread_mode_pause_reset(all, thread) == (t_thread_mode)STOP)
			return (NULL);

		// if (all->render_hitbox)
		// 	tri_lib()->erase_render(all->render_hb);
		// iter_rays(all, thread, get_closest_color);
		// if (get_thread_mode_pause(all, thread) == (t_thread_mode)STOP)
		// 	return (NULL);
		// else if (thread->mode ==(t_thread_mode)RESET)
		// 	continue ;

		// // iter_rays(all, thread, get_diffuse_light);

		// if (iter_rays_line_stop(all, thread, get_diffuse_light) == (t_thread_mode)STOP)
		// 	return (NULL);
		// else if (thread->mode ==(t_thread_mode)RESET)
		// 	continue ;

		// if (start_rays_thread(all, thread) == (t_thread_mode)STOP)
		// 	return (NULL);

		
		// if (start_rays_thread_line(all, thread) == (t_thread_mode)STOP)
		// 	return (NULL);
		// else if (thread->mode ==(t_thread_mode)RESET)
			// continue ;

		if (iter_rays_line_stop(all, thread, traceray) == (t_thread_mode)STOP)
			return (NULL);
		else if (thread->mode ==(t_thread_mode)RESET)
			continue ;

		if (get_thread_mode_pause_continue(all, thread) == (t_thread_mode)STOP)
			return (NULL);
	}
	return (NULL);
}

void	change_threads_mode(t_all *all, t_thread_mode mode)
{
	pthread_mutex_lock(&all->mutex);
	if (all->thread_mode != mode)
		all->thread_mode = mode;
	pthread_mutex_unlock(&all->mutex);
	while (1)
	{
		usleep(200);
		pthread_mutex_lock(&all->mutex);
		if (all->thread_states[mode] == all->n_thread)
		{
			pthread_mutex_unlock(&all->mutex);
			return ;
		}
		pthread_mutex_unlock(&all->mutex);
	}
}

void	draw_rays_to_render(t_all *all, t_render *render)
{
	int				index[2];
	int				real[2];
	const int		mi_pix = all->canvas.pixel_values >> 1;

	index[0] = mi_pix;
	real[0] = 0;
	// change_threads_mode(all, PAUSE);
	while (real[0] < all->win_height)
	{
		real[1] = 0;
		index[1] = mi_pix;
		index[0] -= (index[0] >= all->win_height);
		while (real[1] < all->win_width)
		{
			index[1] -= (index[1] >= all->win_width);
			_replace_s_px_on_render((t_render *)render,
				rgb_f_to_unsigned(all->canvas.rays[index[0]][index[1]].color_ray),
				(t_point2d){real[1], real[0]}, all->canvas.pixel_values);
			real[1] += all->canvas.pixel_values;
			index[1] = real[1] + mi_pix;
		}
		real[0] += all->canvas.pixel_values;
		index[0] = real[0] + mi_pix;
	}
	// change_threads_mode(all, CONTINUE);
}

int	end_thread(t_all *all, unsigned int n_thread)
{
	unsigned int	i;

	pthread_mutex_lock(&all->mutex);
	if (all->thread_mode != STOP)
		all->thread_mode = STOP;
	pthread_mutex_unlock(&all->mutex);
	while (1)
	{
		usleep(200);
		pthread_mutex_lock(&all->mutex);
		if (all->thread_states[STOP] == n_thread)
			break ;
		pthread_mutex_unlock(&all->mutex);
	}
	i = 0;
	while (i < n_thread)
		pthread_join(all->threads[i++].thread, NULL);
	free(all->threads);
	all->threads = NULL;
	return (1);
}

//	if (thread->start % all->canvas.pixel_values)
//		real[0] = (thread->start / all->canvas.pixel_values) * all->canvas.pixel_values;
//	else
//		real[0] = thread->start;
//
void	distribute_lines_threads(t_all *all)
{
	unsigned int	i;
	unsigned int	n_lines;

	i = 0;
	n_lines = (int)((double)WIN_HEIGHT_ALL / (double)all->canvas.pixel_values / (double)all->n_thread) * all->canvas.pixel_values;
	// change_threads_mode(all, PAUSE);
	while (i < all->n_thread)
	{
		all->threads[i].start = i * n_lines;
		if (i + 1 == all->n_thread)
			all->threads[i].end = WIN_HEIGHT_ALL;
		else
			all->threads[i].end = all->threads[i].start + n_lines;
		// printf("Pixel_val = %i, Thread %u, start %i end %i\n", all->canvas.pixel_values, i, all->threads[i].start, all->threads[i].end);
		++i;
	}
	// change_threads_mode(all, CONTINUE);
}

int	launch_threads(t_all *all)
{
	unsigned int	i;
	unsigned int	n_lines;
	// unsigned int	actual_line;

	all->n_thread = sysconf(_SC_NPROCESSORS_ONLN) - 1;
	if (all->n_thread <= 0)
		return (1);
	all->threads = malloc(all->n_thread * sizeof(t_threads));
	if (!all->threads)
		return (1);
	all->thread_mode = PAUSE;
	all->thread_states[(t_thread_mode)PAUSE] = 0;
	all->thread_states[(t_thread_mode)CONTINUE] = 0;
	all->thread_states[(t_thread_mode)STOP] = 0;
	all->thread_states[(t_thread_mode)RESET] = 0;
	pthread_mutex_init(&all->mutex, NULL);
	i = 0;
	n_lines = (int)((double)WIN_HEIGHT_ALL / (double)all->canvas.pixel_values / (double)all->n_thread) * all->canvas.pixel_values;
	// actual_line = 0;
	pthread_mutex_lock(&all->mutex);
	while (i < all->n_thread)
	{
		all->threads[i].start = i * n_lines;
		if (i + 1 == all->n_thread)
			all->threads[i].end = WIN_HEIGHT_ALL;
		else
			all->threads[i].end = all->threads[i].start + n_lines;
		// printf("Pixel_val = %i, Thread %u, start %i end %i\n", all->canvas.pixel_values, i, all->threads[i].start, all->threads[i].end);
		all->threads[i].average_time = 0;
		all->threads[i].all = all;
		all->threads[i].mode = PAUSE;
		++all->thread_states[(t_thread_mode)PAUSE];
		gettimeofday(&all->threads[i].start_time, NULL);
		if (pthread_create(&all->threads[i].thread, NULL, thread_routine, all->threads + i))
			return (end_thread(all, all->thread_states[(t_thread_mode)PAUSE] - 1));
		++i;
	}
	pthread_mutex_unlock(&all->mutex);
	return (0);
}
