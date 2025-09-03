#include "miniRT.h"
#include "tri_lib.h"
#include <time.h>

static int	in_readfile(char **final, char **buf, int fd, int i)
{
	ssize_t	rd;

	rd = (BUFF_SIZE << i);
	(*buf) = malloc(sizeof(char) * (rd + 1));
	if (!(*buf))
		return (printf("Error: buffer malloc\n"), 0);
	rd = read(fd, (*buf), rd);
	if (!rd)
		return (2);
	else if (rd == -1 && (*final))
		return (free((*buf)), free((*final)), 0);
	else if (rd == -1 && !(*final))
		return (free((*buf)), 0);
	(*buf)[rd] = 0;
	(*final) = ft_strjoin((*final), (*buf));
	if (!(*final))
		return (free((*buf)), printf("Error: buffer malloc error\n"), 0);
	free((*buf));
	return (1);
}

char	*readfile(int fd)
{
	int		code;
	char	*buf;
	char	*final;
	int		i;

	final = NULL;
	i = 0;
	while (1)
	{
		code = in_readfile(&final, &buf, fd, i);
		if (!code)
			return (NULL);
		else if (code == 2)
			break ;
		i += (i < 18);
	}
	free(buf);
	return (final);
}

int	move_point(t_tri_lib *lib, t_coord *point, t_vec *dir, double amount)
{
	t_vec	tmp;

	add_vectors(point, scalar_multiplication(dir,
			get_fps_delta_f(lib, amount), &tmp), point);
	return (1);
}

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

int	looped(t_tri_lib *lib, void *a)
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

int	on_configure(int x, int y, void *param)
{
	(void)param;
	printf("(%i,%i)\n", x, y);
	return (0);
}

// Dans main

int	main(int argc, char **argv)
{
	t_all	*all;
	t_win	*win;

	if (argc < 2)
		return (printf("Not enough arguments\n"), 1);
	all = __get_all();
	if (__init__(all, argv, argc))
		return (free_all(all), 1);
	tri_lib()->init();
	tri_lib()->auto_draw = 1;
	tri_lib()->get_end_function(free_all);
	tri_lib()->_user_content = all;
	win = tri_lib()->create_window("QQQQQQQQQQQ",
			all->win_width, all->win_height);
	win->auto_draw = 1;
	start_rays(all);
	tri_lib()->draw_windows();
	_main_loop(looped, (void *)all);
	free_all(all);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_all	*all;
// 	t_win	*win;

// 	if (argc < 2)
// 		return (printf("Not enough arguments\n"), 1);
// 	all = __get_all();
// 	if (__init__(all, argv, argc))
// 		return (free_all(all), 1);
// 	tri_lib()->init();
// 	tri_lib()->auto_draw = 1;
// 	tri_lib()->get_end_function(free_all);
// 	tri_lib()->_user_content = all;
// 	win = tri_lib()->create_window("QQQQQQQQQQQ",
// 			all->win_width, all->win_height);
// 	win->auto_draw = 1;
// 	start_rays(all);
// 	tri_lib()->draw_windows();
// 	#ifndef NOLOOP
// 		tri_lib()->loop(looped, (void *)all);
// 	#else
// 		tri_lib()->quit();
// 	#endif
// 	return (0);
// }
