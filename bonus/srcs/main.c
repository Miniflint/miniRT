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

void print_bvh_dot(t_hitbox *node, FILE *file)
{
	if (!node)
		return;
	if (node->node_type == LEAF)
	{
		if (node->type == SPHERE)
			fprintf(file, "\t\"%p\" [label=\"SPHERE\"];\n", (void *)node);
		if (node->type == BOX)
			fprintf(file, "\t\"%p\" [label=\"BOX\"];\n", (void *)node);
		if (node->type == CYLINDER)
			fprintf(file, "\t\"%p\" [label=\"CYLINDER\"];\n", (void *)node);
	}
	else if (node->node_type == INTERNAL)
		fprintf(file, "\t\"%p\" [label=\"INTERNAL\"];\n", (void *)node);
	else if (node->node_type == ROOT)
		fprintf(file, "\t\"%p\" [label=\"ROOT\"];\n", (void *)node);
	if (node->left)
	{
		fprintf(file, "\t\"%p\" -> \"%p\";\n", (void *)node, (void *)node->left);
		print_bvh_dot(node->left, file);
	}
	if (node->right)
	{
		fprintf(file, "\t\"%p\" -> \"%p\";\n", (void *)node, (void *)node->right);
		print_bvh_dot(node->right, file);
	}
}

void export_bvh_to_dot(t_hitbox *root)
{
	FILE *f;

	f = fopen("out.dot", "w");
	fprintf(f, "digraph BVH {\n");
	print_bvh_dot(root, f);
	fprintf(f, "}\n");
	fclose(f);
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
	export_bvh_to_dot(all->bvh);
	tri_lib()->init();
	tri_lib()->auto_draw = 1;
	tri_lib()->get_end_function(free_all);
	tri_lib()->_user_content = all;
	win = tri_lib()->create_window("QQQQQQQQQQQ",
			all->win_width, all->win_height);
	all->render_hb = tri_lib()->create_render(win);
	win->auto_draw = 1;
	launch_threads(all);
	usleep(1000);
	change_threads_mode(all, CONTINUE);
	// start_rays(all);
	tri_lib()->draw_windows();
	_main_loop(looped, (void *)all);
	free_all(all);
	return (0);
}
