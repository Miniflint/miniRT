#include "miniRT.h"

#ifdef SSAA

void	ft_zeroes(t_all *all)
{
	all->ambient_light.ratio = 0;
	all->ambient_light.rgb = (t_rgb){0, 0, 0, 0};
	all->ambient_light.nb = 0;
	all->camera.viewpoint = (t_coord){0, 0, 0};
	all->camera.nb = 0;
	all->camera.dir = (t_vec){0, 0, 0};
	all->camera.fov = 0;
	all->line_count = 1;
	all->cylinders = NULL;
	all->objects = NULL;
	all->spheres = NULL;
	all->planes = NULL;
	all->lights = NULL;
	all->win_width = WIN_WIDTH_ALL * 2;
	all->win_height = WIN_HEIGHT_ALL * 2;
	all->shadow_on = 1;
	all->render_on = 1;
	all->canvas.pixel_values = 2;
	all->light_ratio = 1;
	all->distance_light = DISTANCE_LIGHT_MIDDLE * DISTANCE_LIGHT_MIDDLE;
	all->threads = NULL;
	all->nb_shapes = 0;
	all->render_hitbox = 1;
}

#else

void	ft_zeroes(t_all *all)
{
	all->ambient_light.ratio = 0;
	all->ambient_light.rgb = (t_rgb){0, 0, 0, 0};
	all->ambient_light.nb = 0;
	all->camera.viewpoint = (t_coord){0, 0, 0};
	all->camera.nb = 0;
	all->camera.dir = (t_vec){0, 0, 0};
	all->camera.fov = 0;
	all->line_count = 1;
	all->cylinders = NULL;
	all->objects = NULL;
	all->spheres = NULL;
	all->planes = NULL;
	all->lights = NULL;
	all->win_width = WIN_WIDTH_ALL;
	all->win_height = WIN_HEIGHT_ALL;
	all->shadow_on = 1;
	all->render_on = 1;
	all->canvas.pixel_values = 3;
	all->light_ratio = 1;
	all->distance_light = DISTANCE_LIGHT_MIDDLE * DISTANCE_LIGHT_MIDDLE;
	all->threads = NULL;
	all->nb_shapes = 0;
	all->render_hitbox = 1;
}

#endif

int	__parse_file_scene(t_all *all)
{
	char		*str;
	char		*tmp;
	const int	fd = open(all->argv[1], O_RDONLY);

	if (fd == -1)
		return (printf("File cannot be accessed\n"), 1);
	str = readfile(fd);
	close(fd);
	if (!str)
		return (
			printf("File is empty/error occured while trying to read\n"), 1);
	tmp = str;
	if (__set_values_scene(all, &str) == 1)
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

void	zeroes_two(t_object *object, char *path)
{
	int	i;

	object->indexes[I_POINTS] = 0;
	object->indexes[I_FACES] = 0;
	object->i_vertice[I_VT] = 0;
	object->i_vertice[I_VN] = 0;
	object->i_vertice[I_V] = 0;
	object->nb_vertices = 0;
	object->line_count = 1;
	object->nb_points = 0;
	object->nb_faces = 0;
	object->name[0] = 0;
	object->coord = (t_coord){0, 0, 0};
	i = -1;
	while (path[++i])
		object->path[i] = path[i];
	object->path[i] = 0;
	while (++i < 256)
		object->path[i] = 0;
	i = -1;
	while (++i < 128)
		object->curr_group[i] = 0;
}

int	init_canvas(t_all *all, t_canvas *canvas)
{
	int	i;

	canvas->rays = NULL;
	canvas->rays_save = NULL;
	canvas->pix_y = NULL;
	canvas->pix_x = NULL;
	canvas->rays = malloc((all->win_height + 1) * sizeof(t_ray *));
	if (!canvas->rays)
		return (1);
	canvas->rays[0] = NULL;
	canvas->rays_save = malloc((all->win_height + 1) * sizeof(t_ray *));
	if (!canvas->rays_save)
		return (1);
	canvas->rays_save[0] = NULL;
	canvas->pix_y = malloc((all->win_height) * sizeof(double));
	if (!canvas->pix_y)
		return (1);
	canvas->pix_x = malloc((all->win_width) * sizeof(double));
	if (!canvas->pix_x)
		return (1);
	i = 0;
	while (i < all->win_height)
	{
		canvas->rays[i] = malloc((all->win_width) * sizeof(t_ray));
		if (!canvas->rays[i])
			return (1);
		canvas->rays_save[i] = malloc((all->win_width) * sizeof(t_ray));
		if (!canvas->rays_save[i])
			return (1);
		i++;
	}
	return (0);
}

int	__init__(t_all *all, char **argv, int argc)
{
	ft_zeroes(all);
	if (init_canvas(all, &all->canvas))
		return (1);
	all->argv = argv;
	all->argc = argc;
	if (check_ext(all->argv))
		return (1);
	printf("all0\n");
	if (__parse_file_scene(all))
		return (1);
	printf("all0\n");
	if (all->ambient_light.nb <= 0)
		return (printf("Error: you must have 1 ambient light\n"), 1);
	if (all->camera.nb <= 0)
		return (printf("Error: you must have 1 camera\n"), 1);
	if (__parse_file_objs(all))
		return (1);
	printf("all0\n");
	apply_rgb_all_shape(all);
	printf("all1\n");
	all->nb_items = all->nb_shapes + get_depth_objs(all->objects);
	printf("all2\n");
	//print_all_structs(all);
	create_shape_array(all);
	printf("all3\n");
	sort_shape(all->shapes);
	all->bvh = create_bvh_iter(all, all->nb_shapes, 0);
	printf("all4\n");
	if (all->bvh->node_type != LEAF)
		all->bvh->node_type = ROOT;
	printf("all5\n");
	make_perpendicular(&all->camera);
	printf("all6\n");
	cal_fov(all);
	return (0);
}
