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

void print_bvh_dot_iter(t_hitbox *root, FILE *file)
{
	t_queue 	q;
	t_hitbox	*curr;

	if (queue_init(&q, __get_all()->nb_shapes + get_depth_objs(__get_all()->objects)))
		return ;
	queue_push(&q, root);
	while (!queue_is_empty(&q))
	{
		curr = queue_pop(&q);
		if (!curr)
			continue ;
		//printf("[label=\"%p\"];\n", (void *)curr);
		if (curr->node_type == LEAF)
		{
			if (curr->type == SPHERE)
				fprintf(file, "\t\"%p\" [label=\"SPHERE\"];\n", (void *)curr);
			else if (curr->type == BOX)
				fprintf(file, "\t\"%p\" [label=\"BOX\"];\n", (void *)curr);
			else if (curr->type == CYLINDER)
				fprintf(file, "\t\"%p\" [label=\"CYLINDER\"];\n", (void *)curr);
			else if (curr->type == TRIANGLE)
				fprintf(file, "\t\"%p\" [label=\"TRIANGLE\"];\n", (void *)curr);
		}
		else
		{
			if (curr->node_type == INTERNAL)
				fprintf(file, "\t\"%p\" [label=\"%p\"];\n", (void *)curr, (void *)curr);
			else if (curr->node_type == ROOT)
				fprintf(file, "\t\"%p\" [label=\"%p\"];\n", (void *)curr, (void *)curr);
			if (curr->left)
			{
				fprintf(file, "\t\"%p\" -> \"%p\";\n", (void *)curr, (void *)curr->left);
				queue_push(&q, curr->left);
			}
			if (curr->right)
			{
				fprintf(file, "\t\"%p\" -> \"%p\";\n", (void *)curr, (void *)curr->right);
				queue_push(&q, curr->right);
			}
		}
	}
	queue_free(&q);
}

void export_bvh_to_dot(t_hitbox *root)
{
	FILE *f;

	f = fopen("out.dot", "w");
	fprintf(f, "digraph BVH {\n");
	print_bvh_dot_iter(root, f);
	fprintf(f, "}\n");
	fclose(f);
}

#ifdef SSAA
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
	export_bvh_to_dot(all->bvh);
	tri_lib()->init();
	tri_lib()->auto_draw = 1;
	tri_lib()->get_end_function(free_all);
	tri_lib()->_user_content = all;
	win = tri_lib()->create_window("QQQQQQQQQQQ",
			WIN_WIDTH_ALL, WIN_HEIGHT_ALL);
	all->render_hb = tri_lib()->create_render(win);
	win->auto_draw = 1;
#ifndef BVH
	printf("BVH OFF\n");
#else
	printf("BVH ON\n");
#endif
#ifdef THREADS
	printf("threads on\n");
	launch_threads(all);
	usleep(10000);
	change_threads_mode(all, CONTINUE);
#else
	printf("threads off\n");
	start_rays(all);
#endif

	tri_lib()->draw_windows();
	_main_loop(looped, (void *)all);
	free_all(all);
	return (0);
}

#else

// Dans main
int	main(int argc, char **argv)
{
	t_all	*all;
	t_win	*win;

	if (argc < 2)
		return (printf("Not enough arguments\n"), 1);
	printf("sizeof tray: %lu\n", sizeof(t_ray));
	printf("sizeof tray: %lu\n", sizeof(t_rgb_f));
	printf("aaaaaaaaa\n");
	fflush(stdout);
	all = __get_all();
	if (__init__(all, argv, argc))
		return (free_all(all), 1);
	export_bvh_to_dot(all->bvh);
	tri_lib()->init();
	tri_lib()->auto_draw = 1;
	tri_lib()->get_end_function(free_all);
	tri_lib()->_user_content = all;
	win = tri_lib()->create_window("QQQQQQQQQQQ",
			all->win_width, all->win_height);
	all->render_hb = tri_lib()->create_render(win);
	win->auto_draw = 1;
#ifndef BVH
	printf("BVH OFF\n");
#else
	printf("BVH ON\n");
#endif
#ifdef THREADS
	printf("threads on\n");
	launch_threads(all);
	usleep(10000);
	change_threads_mode(all, CONTINUE);
#else
	printf("threads off\n");
	start_rays(all);
#endif

	tri_lib()->draw_windows();
	_main_loop(looped, (void *)all);
	free_all(all);
	return (0);
}

#endif
