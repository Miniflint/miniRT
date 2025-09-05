#include "miniRT.h"
#include "tri_lib.h"
#include <time.h>

int	move_point(t_tri_lib *lib, t_coord *point, t_vec *dir, double amount)
{
	t_vec	tmp;

	add_vectors(point, scalar_multiplication(dir,
			get_fps_delta_f(lib, amount), &tmp), point);
	return (1);
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
