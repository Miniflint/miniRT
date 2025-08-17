#include "miniRT.h"
#include "tri_lib.h"
#include <time.h>

char	*readfile(int fd)
{
	ssize_t		rd;
	char	*buf;
	char	*final;
	int		i;

	final = NULL;
	i = 0;
	while (1)
	{
		rd = (BUFF_SIZE << i);
		buf = malloc(sizeof(char) * (rd + 1));
		if (!buf)
			return (printf("Error: buffer malloc\n"), NULL);
		rd = read(fd, buf, rd);
		if (!rd)
			break ;
		else if (rd == -1 && final)
			return (free(buf), free(final), NULL);
		else if (rd == -1 && !final)
			return (free(buf), NULL);
		buf[rd] = 0;
		final = ft_strjoin(final, buf);
		if (!final)
			return (free(buf), printf("Error: buffer malloc error\n"), NULL);
		free(buf);
		i += (i < 18);
	}
	free(buf);
	return (final);
}

int	move_point(t_tri_lib *lib, t_coord *point, t_vec *dir, double amount)
{
	t_vec	tmp;

	add_vectors(point, scalar_multiplication(dir, get_fps_delta_f(lib, amount), &tmp), point);
	return (1);
}

void	event_key_press(t_tri_lib *lib, void *a)
{
	t_all	*all;
	int	start;
	///unsigned long elapsed_time;
	// static int		refresh = 0;

	start = 0;
	all = (t_all *)a;
	// ++refresh;
	// get_fps_tick(FPS_MAX, &elapsed_time, 1);
	// !get_fps_tick(FPS_MAX, &elapsed_time, 0)
	if (lib->event && lib->event->type == KEY_PRESS)
	{
		if (lib->event->key_id >= '1' && lib->event->key_id <= '9')
		{
			start = 2;
			all->canvas.pixel_values = ((lib->event->key_id - '0') << 1) - 1;
			lib->erase_render(&lib->event->win_id->_base_render._render);
		}
		if (lib->event->key_id == 'k')
		{
			start = 2;
			all->shadow_on = !all->shadow_on;
		}
		if (lib->event->key_id == 'v')
		{
			start = 2;
			all->light_ratio -= 0.01;
		}
		if (lib->event->key_id == KEY_ESC)
			lib->quit();
	}
	if (lib->_windows->event.key['w'])
		start = move_point(lib, &all->camera.viewpoint, &all->camera.dir, 3);
	if (lib->_windows->event.key['a'])
		start = move_point(lib, &all->camera.viewpoint, &all->camera.dir_x, -3);
	if (lib->_windows->event.key['s'])
		start = move_point(lib, &all->camera.viewpoint, &all->camera.dir, -3);
	if (lib->_windows->event.key['d'])
		start = move_point(lib, &all->camera.viewpoint, &all->camera.dir_x, 3);
	if (lib->_windows->event.key['q'])
		start = move_point(lib, &all->camera.viewpoint, &all->camera.dir_y, 3);
	if (lib->_windows->event.key['e'])
		start = move_point(lib, &all->camera.viewpoint, &all->camera.dir_y, -3);
	if (lib->_windows->event.key['n'])
	{
		start = 2;
		all->camera.fov += get_fps_delta_f(lib, (all->camera.fov < 179) * 0.5);
	}
	if (lib->_windows->event.key['m'])
	{
		start = 2;
		all->camera.fov -= get_fps_delta_f(lib, (all->camera.fov > 1) * 0.5);
	}
	if (lib->_windows->event.key['p'])
	{
		start = 1;
		all->canvas.pixel_values += (all->canvas.pixel_values < 253) << 1;
		// lib->erase_render(&lib->event->win_id->_base_render._render);
	}
	if (lib->_windows->event.key['o'])
	{
		start = 1;
		all->canvas.pixel_values -= (all->canvas.pixel_values > 1) << 1;
		// lib->erase_render(&lib->event->win_id->_base_render._render);
	}
	if (lib->_windows->event.key[KEY_UP])
	{
		start = 3;
		rotate_camera_x(&all->camera.dir, get_fps_delta_f(lib, MOVE_CAM_SPEED));
		make_perpendicular(&all->camera);
	}
	if (lib->_windows->event.key[KEY_DOWN])
	{
		start = 3;
		rotate_camera_x(&all->camera.dir, get_fps_delta_f(lib, -MOVE_CAM_SPEED));
		make_perpendicular(&all->camera);
	}
	if (lib->_windows->event.key[KEY_LEFT])
	{
		start = 3;
		if (!lib->_windows->event.key[KEY_SHIFT_LEFT])
			rotate_camera_z(&all->camera.dir, get_fps_delta_f(lib, -MOVE_CAM_SPEED));
		else
			rotate_camera_y(&all->camera.dir, get_fps_delta_f(lib, -MOVE_CAM_SPEED));
		make_perpendicular(&all->camera);
	}
	if (lib->_windows->event.key[KEY_RIGHT])
	{
		start = 3;
		if (!lib->_windows->event.key[KEY_SHIFT_LEFT])
			rotate_camera_z(&all->camera.dir, get_fps_delta_f(lib, MOVE_CAM_SPEED));
		else
			rotate_camera_y(&all->camera.dir, get_fps_delta_f(lib, MOVE_CAM_SPEED));
		make_perpendicular(&all->camera);
	}
	if (lib->_windows->event.key['y'])
	{
		start = 2;
		all->distance_light -= get_fps_delta_f(lib, DISTANCE_LIGHT_MIDDLE * 2);
	}
	if (lib->_windows->event.key['u'])
	{
		start = 2;
		all->distance_light += get_fps_delta_f(lib, DISTANCE_LIGHT_MIDDLE * 2);
	}
	// if (refresh > 5 && start)
	if (start)
	{
		// refresh = 0;
		if (start == 2)
			cal_fov(all);
		else if (start == 3)
			cal_rays(all);
		else
			reset_rays(all);
		start_rays(all);
	}
}

int looped(t_tri_lib *lib, void *a)
{
	(void)a;
	event_key_press(lib, a);
	if (lib->event && lib->event->type == MOUSE_RIGHT_PRESS)
		printf("AAAAA\n");
	return (0);
}

int	mouse(int button, int x, int y, void *param)
{
	(void)param;
	printf("%d, P(%i,%i)\n", button, x, y);
	return (0);
}
int on_configure(int x, int y, void *param)
{
	(void)param;
	printf("(%i,%i)\n", x, y);
    return (0);
}

// Dans main

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc < 2)
		return (printf("Not enough arguments\n"), 1);
	all = __get_all();
	if (__init__(all, argv, argc))
		return (free_all(all), 1);
	tri_lib()->init();
	// tri_lib()->auto_draw = 1;
	tri_lib()->get_end_function(free_all);
	tri_lib()->_user_content = all;
	tri_lib()->create_window("QQQQQQQQQQQ", all->win_width, all->win_height)->auto_draw = 1;
	start_rays(all);
	tri_lib()->draw_windows();
	#ifndef NOLOOP
		tri_lib()->loop(looped, all);
	#else
		tri_lib()->quit();
	#endif
	return (0);
}
