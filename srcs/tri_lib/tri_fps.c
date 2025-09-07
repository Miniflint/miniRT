/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_fps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 02:44:58 by hermesrolle       #+#    #+#             */
/*   Updated: 2025/09/07 02:44:59 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"
#include "tri_mlx_code.h"
#include <stdio.h>

double	_get_fps(struct timeval *last)
{
	struct timeval	now;
	unsigned long	delta_us;
	double			fps;

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
	return ((double)((double)(value) *(double)lib->fps_delta + 0.5));
}

long unsigned int	get_fps_delta_u(t_tri_lib *lib, long unsigned int value)
{
	return ((double)((double)(value) *(double)lib->fps_delta + 0.5));
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
// 	actual_time
// = (unsigned long)((tv.tv_sec % 1000) * 1000) + (tv.tv_usec / 1000);
// 	*ret = (actual_time - last_fps);
// 	if (reset || *ret >= ms)
// 	{
// 		last_fps = actual_time;
// 		return (1);
// 	}
// 	return (0);
// }

int	_get_tick_fps(t_tri_lib *lib, struct timeval *last, double *ret_fps)
{
	struct timeval	now;
	unsigned long	delta_us;
	double			fps;

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
