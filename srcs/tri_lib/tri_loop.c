/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:28:01 by herolle           #+#    #+#             */
/*   Updated: 2025/08/17 01:37:00 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"
#include "tri_mlx_code.h"
#include <stdio.h>

double _get_fps(struct timeval *last)
{
	struct timeval now;
	unsigned long delta_us;
	double fps;

	gettimeofday(&now, NULL);
	delta_us = (now.tv_sec - last->tv_sec) * 1000000UL
			 + (now.tv_usec - last->tv_usec);
	*last = now;
	if (delta_us > 0)
		fps = 1000000.0 / (double)delta_us;
	else
		fps = 0.0;
	return (fps);
}

// int _get_tick_fps(t_tri_lib *lib, struct timeval *last, double *ret_fps)
// {
// 	struct timeval now;
// 	unsigned long delta_us;
// 	double fps;

// 	gettimeofday(&now, NULL);
// 	delta_us = (now.tv_sec - last->tv_sec) * 1000000UL
// 			 + (now.tv_usec - last->tv_usec);
// 	if (delta_us > 0)
// 		fps = 1000000.0 / (double)delta_us;
// 	else
// 		fps = 0.0;
// 	if (fps < lib->fps_max)
// 		return (0);
// 	*last = now;
// 	*ret_fps = fps;
// 	return (1);
// }

double	get_fps_delta_f(t_tri_lib *lib, double value)
{
	return (value * lib->fps_delta);
}

long int	get_fps_delta_i(t_tri_lib *lib, long int value)
{
	return ((double)((double)(value) * lib->fps_delta + 0.5));
}

long unsigned int	get_fps_delta_u(t_tri_lib *lib, long unsigned int value)
{
	return ((double)((double)(value) * lib->fps_delta + 0.5));
}

// char	_get_fps_tick(unsigned int fps, unsigned long *ret, int reset)
// {
// 	struct timeval			tv;
// 	static unsigned long	last_fps = 0;
// 	unsigned long			actual_time;

// 	gettimeofday(&tv, NULL);
// 	actual_time = (unsigned long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
// 	*ret = (actual_time - last_fps);
// 	if (reset || *ret >= 1000 / fps)
// 	{
// 		last_fps = actual_time;
// 		return (1);
// 	}
// 	return (0);
// }

// char	_get_tick(unsigned int ms, unsigned long *ret, int reset)
// {
// 	struct timeval			tv;
// 	static unsigned long	last_fps = 0;
// 	unsigned long			actual_time;

// 	gettimeofday(&tv, NULL);
// 	actual_time = (unsigned long)((tv.tv_sec % 1000) * 1000) + (tv.tv_usec / 1000);
// 	*ret = (actual_time - last_fps);
// 	if (reset || *ret >= ms)
// 	{
// 		last_fps = actual_time;
// 		return (1);
// 	}
// 	return (0);
// }

int _get_tick_fps(t_tri_lib *lib, struct timeval *last, double *ret_fps)
{
	struct timeval now;
	unsigned long delta_us;
	double fps;

	gettimeofday(&now, NULL);
	delta_us = (now.tv_sec - last->tv_sec) * 1000000UL
			 + (now.tv_usec - last->tv_usec);
	if (delta_us > 0)
		fps = 1000000.0 / (double)delta_us;
	else
		fps = 0.0;
	if (fps > lib->fps_max)
		return (0);
	*last = now;
	*ret_fps = fps;
	return (1);
}

void	_call_user_main(t_tri_lib *lib)
{
	double	fps;

	if (lib->fps_max < TRI_INF_FPS)
	{
		while (!_get_tick_fps(lib, &lib->last_loop, &lib->fps))
			;
	}
	else
		lib->fps = _get_fps(&lib->last_loop);
		if (lib->fps <= 0)
		fps = 0.01;
	else
		fps = lib->fps;
	lib->fps_delta = lib->fps_target / fps;
	if (lib->fps_delta < 0.05)
		lib->fps_delta = 0.05;
	else if (lib->fps_delta > 4.0)
	lib->fps_delta = 4;
	lib->_user_main(lib, lib->_user_content);
	_auto_draw(lib);
}

static int	_loop_event(t_tri_lib *lib)
{
	lib->event = NULL;
	_call_user_main(lib);
	return (0);
}

static int	_close_window(t_win *win)
{
	t_tri_lib	*lib;

	lib = tri_lib();
	lib->destroy_window(win);
	if (!lib->_windows)
		lib->quit();
	return (1);
}

int	_main_loop(int (*f)(t_tri_lib *, void *), void *content)
{
	t_tri_lib	*lib;
	t_win		*cursor_win;

	lib = tri_lib();
	if (!lib->_mlx)
		return (TRI_UNITIALISED);
	lib->_user_main = f;
	lib->_user_content = content;
	cursor_win = lib->_windows;
	while (cursor_win && cursor_win->_win)
	{
		mlx_hook(cursor_win->_win, MLX_KEY_PRESS_HOOK, (1L << 0), _get_key_press, cursor_win);
		mlx_hook(cursor_win->_win, MLX_KEY_RELEASE_HOOK, (1L << 1), _get_key_release, cursor_win);
		mlx_hook(cursor_win->_win, 17, 0, _close_window, cursor_win);
		mlx_hook(cursor_win->_win, MLX_MOUSE_PRESS_HOOK, 1L << 2, _get_mouse_press, cursor_win);
		mlx_hook(cursor_win->_win, MLX_MOUSE_RELEASE_HOOK, 1L << 3, _get_mouse_release, cursor_win);
			mlx_hook(cursor_win->_win, MLX_MOUSE_MOVE_HOOK, 1L << 6, _get_mouse_move, cursor_win);
		cursor_win = cursor_win->_next;
	}
	mlx_loop_hook(lib->_mlx, _loop_event, lib);
	// if (lib->_fps_max <= TRI_INF_FPS)
	// 	while (_get_tick(lib->_tick_size, &lib->last_tick, 0));
	mlx_loop(lib->_mlx);
	return (TRI_SUCCESS);
}
