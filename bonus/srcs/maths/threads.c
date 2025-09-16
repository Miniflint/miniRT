#include "miniRT.h"
#include "tri_colors.h"

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
		--(all->thread_states[thread->mode]);
		thread->mode = all->thread_mode;
		++(all->thread_states[thread->mode]);
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
	while (get_thread_mode(all, thread) == (t_thread_mode)PAUSE
		|| thread->mode == (t_thread_mode)RESET)
		usleep(200);
	return (thread->mode);
}

t_thread_mode	get_thread_mode_pause_continue(t_all *all, t_threads *thread)
{
	while (get_thread_mode(all, thread) == (t_thread_mode)PAUSE
		|| thread->mode == (t_thread_mode)CONTINUE)
		usleep(200);
	return (thread->mode);
}

int	thread_rend_light(t_all *all, t_threads *thread)
{
	if (all->render_on)
	{
		iter_rays(all, thread, init_color_ray);
		if (iter_rays_line_stop(all, thread, get_local_color)
			== (t_thread_mode)STOP)
			return (1);
		else if (thread->mode == (t_thread_mode)RESET)
			return (0);
		while (1)
		{
			if (iter_rays_line_stop(all, thread, traceray_reflection)
				== (t_thread_mode)STOP)
				return (1);
			else if (thread->mode == (t_thread_mode)RESET)
				return (0);
		}
	}
	else if (get_thread_mode_pause_continue(all, thread)
		== (t_thread_mode)STOP)
		return (1);
	return (0);
}

void	*thread_routine(void *content)
{
	t_all		*all;
	t_threads	*thread;

	thread = content;
	all = thread->all;
	while (1)
	{
		if (get_thread_mode_pause_reset(all, thread) == (t_thread_mode)STOP)
			return (NULL);
		if (iter_rays_line_stop(all, thread, get_closest_color)
			== (t_thread_mode)STOP)
			return (NULL);
		else if (thread->mode == (t_thread_mode)RESET)
			continue ;
		if (get_thread_mode_pause(all, thread) == (t_thread_mode)STOP)
			return (NULL);
		else if (thread->mode == (t_thread_mode)RESET)
			continue ;
		if (thread_rend_light(all, thread))
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

#ifdef SSAA

static t_rgb_f	get_color_average(t_all *all, int i, int j)
{
	t_rgb_f	ret;

	ret.r = all->canvas.rays[i][j].color_ray.r * 0.25
		+ all->canvas.rays[i + 1][j].color_ray.r * 0.25
		+ all->canvas.rays[i][j + 1].color_ray.r * 0.25
		+ all->canvas.rays[i + 1][j + 1].color_ray.r * 0.25;
	ret.g = all->canvas.rays[i][j].color_ray.g * 0.25
		+ all->canvas.rays[i + 1][j].color_ray.g * 0.25
		+ all->canvas.rays[i][j + 1].color_ray.g * 0.25
		+ all->canvas.rays[i + 1][j + 1].color_ray.g * 0.25;
	ret.b = all->canvas.rays[i][j].color_ray.b * 0.25
		+ all->canvas.rays[i + 1][j].color_ray.b * 0.25
		+ all->canvas.rays[i][j + 1].color_ray.b * 0.25
		+ all->canvas.rays[i + 1][j + 1].color_ray.b * 0.25;
	return (ret);
}

static unsigned int	color_with_hitbox_ssaa(
	t_rgb_f color, t_all *all, int x, int y)
{
	if (all->render_on)
		return (TRI_OPAQUE_UNSIGNED | (_mix_colors_render_to_render(
					unsigned_to_argb(_get_pixel(all->render_hb, x, y)),
					rgb_f_to_argb(color)) & 0xFFFFFF));
	else
		return (TRI_OPAQUE_UNSIGNED
			| (_get_pixel(all->render_hb, x, y) & 0xFFFFFF));
}

void	draw_rays_to_render_core(
	t_all *all, t_render *render, int index[2], int real[2])
{
	if (all->render_hitbox || !all->render_on)
		_replace_pixel_on_render((t_render *)render,
			color_with_hitbox_ssaa(get_color_average(all,
					index[0], index[1]), all, real[1], real[0]),
			real[1], real[0]);
	else
		_replace_pixel_on_render((t_render *)render,
			rgb_f_to_unsigned(get_color_average(all,
					index[0], index[1])), real[1], real[0]);
}

void	draw_rays_to_render(t_all *all, t_render *render)
{
	int				index[2];
	int				real[2];

	index[0] = 0;
	real[0] = 0;
	while (real[0] < WIN_HEIGHT_ALL)
	{
		real[1] = 0;
		index[1] = 0;
		while (real[1] < WIN_WIDTH_ALL)
		{
			if (all->canvas.rays[index[0]][index[1]].to_draw)
			{
				draw_rays_to_render_core(all, render, index, real);
			}
			++real[1];
			index[1] += 2;
		}
		++real[0];
		index[0] += 2;
	}
}

#else

unsigned int	color_with_hitbox(t_ray *ray, t_all *all, int x, int y)
{
	if (all->render_on)
		return (TRI_OPAQUE_UNSIGNED | (_mix_colors_render_to_render(
					unsigned_to_argb(
						_get_pixel(all->render_hb, x, y)),
					rgb_f_to_argb(ray->color_ray)) & 0xFFFFFF));
	else
		return (TRI_OPAQUE_UNSIGNED | (_get_pixel(all->render_hb, x, y)
				& 0xFFFFFF));
}

void	draw_rays_to_render_core(
		t_all *all, t_render *render, int index[2], int real[2])
{
	if (index[1] >= all->win_width)
		index[1] = all->win_width - 1;
	if (all->canvas.rays[index[0]][index[1]].to_draw)
	{
		if (all->render_hitbox || !all->render_on)
			_replace_s_px_on_render((t_render *)render,
				color_with_hitbox(&all->canvas.rays[index[0]][index[1]],
					all, index[1], index[0]),
				(t_point2d){real[1], real[0]},
				all->canvas.pixel_values);
		else
			_replace_s_px_on_render((t_render *)render,
				rgb_f_to_unsigned(
					all->canvas.rays[index[0]][index[1]].color_ray),
				(t_point2d){real[1], real[0]}, all->canvas.pixel_values);
		all->canvas.rays[index[0]][index[1]].to_draw = 0;
	}
}

void	draw_rays_to_render(t_all *all, t_render *render)
{
	int				index[2];
	int				real[2];
	const int		mi_pix = all->canvas.pixel_values >> 1;

	index[0] = mi_pix;
	real[0] = 0;
	while (real[0] < all->win_height)
	{
		real[1] = 0;
		index[1] = mi_pix;
		if (index[0] >= all->win_height)
			index[0] = all->win_height - 1;
		while (real[1] < all->win_width)
		{
			draw_rays_to_render_core(all, render, index, real);
			real[1] += all->canvas.pixel_values;
			index[1] = real[1] + mi_pix;
		}
		real[0] += all->canvas.pixel_values;
		index[0] = real[0] + mi_pix;
	}
}

#endif

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
	i = 0;
	while (i < n_thread)
		queue_free(&all->threads[i++].queue);
	free(all->threads);
	all->threads = NULL;
	return (1);
}

void	distribute_lines_threads(t_all *all)
{
	unsigned int	i;
	unsigned int	n_lines;

	i = 0;
	n_lines = (int)((double)all->win_height
			/ (double)all->canvas.pixel_values
			/ (double)all->n_thread) *all->canvas.pixel_values;
	while (i < all->n_thread)
	{
		all->threads[i].start = i * n_lines;
		if (i + 1 >= all->n_thread)
			all->threads[i].end = all->win_height;
		else
			all->threads[i].end = all->threads[i].start + n_lines;
		if (all->threads[i].end > all->win_height)
			all->threads[i].end = all->win_height;
		++i;
	}
}

int	init_threads(t_all *all)
{
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
	return (0);
}

int	init_one_thread(
		t_threads *thread, t_all *all, unsigned int i, unsigned int n_lines)
{
	if (i + 1 == all->n_thread)
		thread->end = all->win_height;
	else
		thread->end = thread->start + n_lines;
	if (queue_init(&thread->queue, all->nb_items))
		return (1);
	thread->average_time = 0;
	thread->all = all;
	thread->mode = PAUSE;
	++all->thread_states[(t_thread_mode)PAUSE];
	return (0);
}

#ifdef SSAA

int	launch_threads(t_all *all)
{
	unsigned int	i;
	unsigned int	n_lines;

	if (init_threads(all))
		return (1);
	i = 0;
	n_lines = (int)((double)all->win_height / (double)all->n_thread);
	pthread_mutex_lock(&all->mutex);
	while (i < all->n_thread)
	{
		all->threads[i].start = i * n_lines;
		init_one_thread(all->threads + i, all, i, n_lines);
		gettimeofday(&all->threads[i].start_time, NULL);
		if (pthread_create(&all->threads[i].thread, NULL,
				thread_routine, all->threads + i))
			return (end_thread(all,
					all->thread_states[(t_thread_mode)PAUSE] - 1));
		++i;
	}
	pthread_mutex_unlock(&all->mutex);
	return (0);
}

#else

int	launch_threads(t_all *all)
{
	unsigned int	i;
	unsigned int	n_lines;

	if (init_threads(all))
		return (1);
	i = 0;
	n_lines = (int)((double)all->win_height
			/ (double)all->canvas.pixel_values
			/ (double)all->n_thread) *all->canvas.pixel_values;
	pthread_mutex_lock(&all->mutex);
	while (i < all->n_thread)
	{
		all->threads[i].start = i * n_lines;
		init_one_thread(all->threads + i, all, i, n_lines);
		gettimeofday(&all->threads[i].start_time, NULL);
		if (pthread_create(&all->threads[i].thread, NULL,
				thread_routine, all->threads + i))
			return (end_thread(all,
					all->thread_states[(t_thread_mode)PAUSE] - 1));
		++i;
	}
	pthread_mutex_unlock(&all->mutex);
	return (0);
}

#endif
