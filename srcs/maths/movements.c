/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:07:45 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:07:53 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_key_press(t_tri_lib *lib, t_all *all)
{
	if (lib->event->key_id >= '1' && lib->event->key_id <= '9')
	{
		all->canvas.pixel_values = ((lib->event->key_id - '0') << 1) - 1;
		lib->erase_render(&lib->event->win_id->_base_render._render);
		return (2);
	}
	if (lib->event->key_id == 'k')
	{
		all->shadow_on = !all->shadow_on;
		return (2);
	}
	if (lib->event->key_id == 'p')
	{
		all->canvas.pixel_values += (all->canvas.pixel_values < 253) << 1;
		return (1);
	}
	if (lib->event->key_id == 'o')
	{
		all->canvas.pixel_values -= (all->canvas.pixel_values > 1) << 1;
		return (1);
	}
	if (lib->event->key_id == KEY_ESC)
		lib->quit();
	return (0);
}

void	get_cam_move(t_tri_lib *lib, t_all *all, int *start)
{
	if (lib->_windows->event.key['w'])
		*start = move_point(lib, &all->camera.viewpoint, &all->camera.dir, 3);
	if (lib->_windows->event.key['a'])
		*start = move_point(lib, &all->camera.viewpoint,
				&all->camera.dir_x, -3);
	if (lib->_windows->event.key['s'])
		*start = move_point(lib, &all->camera.viewpoint, &all->camera.dir, -3);
	if (lib->_windows->event.key['d'])
		*start = move_point(lib, &all->camera.viewpoint, &all->camera.dir_x, 3);
	if (lib->_windows->event.key['q'])
		*start = move_point(lib, &all->camera.viewpoint, &all->camera.dir_y, 3);
	if (lib->_windows->event.key['e'])
		*start = move_point(lib, &all->camera.viewpoint,
				&all->camera.dir_y, -3);
}

void	get_cam_rotation(t_tri_lib *lib, t_all *all, int *start)
{
	if (lib->_windows->event.key[KEY_UP])
		*start = rotate_camera(&all->camera.dir, &all->camera.dir_x,
				&all->camera.dir_y, get_fps_delta_f(lib, -ROT_CAM_SPEED));
	if (lib->_windows->event.key[KEY_DOWN])
		*start = rotate_camera(&all->camera.dir, &all->camera.dir_x,
				&all->camera.dir_y, get_fps_delta_f(lib, ROT_CAM_SPEED));
	if (lib->_windows->event.key[KEY_LEFT])
	{
		if (!lib->_windows->event.key[KEY_SHIFT_LEFT])
			*start = rotate_camera(&all->camera.dir, &all->camera.dir_y,
					&all->camera.dir_x, get_fps_delta_f(lib, -ROT_CAM_SPEED));
		else
			*start = rotate_camera(&all->camera.dir_x, &all->camera.dir,
					&all->camera.dir_y, get_fps_delta_f(lib, -ROT_CAM_SPEED));
	}
	if (lib->_windows->event.key[KEY_RIGHT])
	{
		if (!lib->_windows->event.key[KEY_SHIFT_LEFT])
			*start = rotate_camera(&all->camera.dir, &all->camera.dir_y,
					&all->camera.dir_x, get_fps_delta_f(lib, ROT_CAM_SPEED));
		else
			*start = rotate_camera(&all->camera.dir_x, &all->camera.dir,
					&all->camera.dir_y, get_fps_delta_f(lib, ROT_CAM_SPEED));
	}
}

void	get_distlight_and_fov(t_tri_lib *lib, t_all *all, int *start)
{
	if (lib->_windows->event.key['n'])
	{
		*start = 2;
		all->camera.fov += get_fps_delta_f(lib, (all->camera.fov < 179) * 0.5);
	}
	if (lib->_windows->event.key['m'])
	{
		*start = 2;
		all->camera.fov -= get_fps_delta_f(lib, (all->camera.fov > 1) * 0.5);
	}
	if (lib->_windows->event.key['y'])
	{
		*start = 2;
		all->distance_light -= get_fps_delta_f(lib, DISTANCE_LIGHT_MIDDLE * 2);
	}
	if (lib->_windows->event.key['u'])
	{
		*start = 2;
		all->distance_light += get_fps_delta_f(lib, DISTANCE_LIGHT_MIDDLE * 2);
	}
}

void	event_key_press(t_tri_lib *lib, void *a)
{
	t_all	*all;
	int		start;

	all = (t_all *)a;
	start = 0;
	if (lib->event && lib->event->type == KEY_PRESS)
		start = get_key_press(lib, all);
	get_cam_move(lib, all, &start);
	get_cam_rotation(lib, all, &start);
	get_distlight_and_fov(lib, all, &start);
	if (start)
	{
		if (start == 2)
			cal_fov(all);
		else if (start == 3)
			cal_rays(all);
		else
			reset_rays(all);
		start_rays(all);
	}
}
