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

void	event_key_press(t_tri_lib *lib, void *a)
{
	t_all	*all;
	t_vec	tmp;
	int	start = 0;
	static int refresh = 0;
	
	all = (t_all *)a;
	refresh++;
	if (lib->_windows->event.key['w'])
	{
		start = 1;
		add_vectors(&all->camera.viewpoint, scalar_multiplication(&all->camera.dir, 1, &tmp), &all->camera.viewpoint);
	}
	if (lib->_windows->event.key['a'])
	{
		start = 1;
		add_vectors(&all->camera.viewpoint, scalar_multiplication(&all->camera.dir_x, -1, &tmp), &all->camera.viewpoint);
	}
	if (lib->_windows->event.key['s'])
	{
		start = 1;
		add_vectors(&all->camera.viewpoint, scalar_multiplication(&all->camera.dir, -1, &tmp), &all->camera.viewpoint);
	}
	if (lib->_windows->event.key['d'])
	{
		start = 1;
		add_vectors(&all->camera.viewpoint, scalar_multiplication(&all->camera.dir_x, 1, &tmp), &all->camera.viewpoint);
	}
	if (lib->_windows->event.key['q'])
	{
		start = 1;
		add_vectors(&all->camera.viewpoint, scalar_multiplication(&all->camera.dir_y, 1, &tmp), &all->camera.viewpoint);
	}
	if (lib->_windows->event.key['e'])
	{
		start = 1;
		add_vectors(&all->camera.viewpoint, scalar_multiplication(&all->camera.dir_y, -1, &tmp), &all->camera.viewpoint);
	}
	if (lib->_windows->event.key['n'])
	{
		start = 3;
		all->camera.fov += ((all->camera.fov < 179) * 0.5);
	}
	if (lib->_windows->event.key['m'])
	{
		start = 3;
		all->camera.fov -= ((all->camera.fov > 1) * 0.5);
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
	if (lib->event && lib->event->type == KEY_PRESS)
	{
		if (lib->event->key_id >= '1' && lib->event->key_id <= '9')
		{
			start = 2;
			all->canvas.pixel_values = ((lib->event->key_id - '0') << 1) - 1;
			// lib->erase_render(&lib->event->win_id->_base_render._render);
		}
	}
	if (refresh > 4 || start == 2)
	{
		refresh = 0;
		if (start)
		{
			clock_t start = clock();
			if (start > 1)
				cal_fov(all);
			else
				reset_rays(all);
			clock_t end = clock();
			float seconds = (float)(end - start) / CLOCKS_PER_SEC;
			printf("rays calculated in %f\n", seconds);
			start = clock();
			start_rays(all);
			end = clock();
			seconds = (float)(end - start) / CLOCKS_PER_SEC;
			printf("rays sent in %f\n", seconds);
		}
	}
	if (lib->event && lib->event->key_id == 'q' && lib->event->key[KEY_BACKSPACE])
		lib->quit();
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
	tri_lib()->get_end_function(free_all);
	tri_lib()->_user_content = all;
	tri_lib()->create_window("QQQQQQQQQQQ", all->win_width, all->win_height);
	start_rays(all);
	tri_lib()->draw_windows();
	#ifndef NOLOOP
		tri_lib()->loop(looped, all);
	#else
		tri_lib()->quit();
	#endif
	return (0);
}
