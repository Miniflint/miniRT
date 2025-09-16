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
	all->canvas.rays = NULL;
	all->canvas.rays_save = NULL;
	all->canvas.pix_x = NULL;
	all->canvas.pix_y = NULL;
	all->canvas.gradient = NULL;
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
	all->canvas.pixel_values = 1;
	all->light_ratio = 1;
	all->distance_light = DISTANCE_LIGHT_MIDDLE * DISTANCE_LIGHT_MIDDLE;
	all->threads = NULL;
	all->nb_shapes = 0;
	all->render_hitbox = 1;
	all->canvas.rays = NULL;
	all->canvas.rays_save = NULL;
	all->canvas.pix_x = NULL;
	all->canvas.pix_y = NULL;
	all->canvas.gradient = NULL;
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

int	init_canvas_utils(t_all *all, t_canvas *canvas)
{
	canvas->gradient = malloc((all->win_height) * sizeof(t_rgb_f));
	if (!canvas->gradient)
		return (1);
	canvas->rays = malloc((all->win_height) * sizeof(t_ray *));
	if (!canvas->rays)
		return (1);
	canvas->rays_save = malloc((all->win_height) * sizeof(t_vec *));
	if (!canvas->rays_save)
		return (1);
	canvas->pix_y = malloc((all->win_height) * sizeof(double));
	if (!canvas->pix_y)
		return (1);
	canvas->pix_x = malloc((all->win_width) * sizeof(double));
	if (!canvas->pix_x)
		return (1);
	return (0);
}

t_rgb_f	get_background_color(int win_height, int i)
{
	double			alpha;
	int				select;
	t_rgb_f const	color[5] = {
	{0.1569, 0.2078, 0.3098},
	{0.2902, 0.3882, 0.5882},
	{0.6, 0.6078, 0.7686},
	{0.9294, 0.6156, 0.5019},
	{0.7098, 0.3725, 0.3412}
	};

	alpha = ((double)i * ((double)4.0 / (double)win_height));
	select = alpha;
	if (select >= 4)
		return (color[4]);
	alpha -= (double)select;
	return ((t_rgb_f){
		color[select + 1].r * alpha + color[select].r * (1.0 - alpha),
		color[select + 1].g * alpha + color[select].g * (1.0 - alpha),
		color[select + 1].b * alpha + color[select].b * (1.0 - alpha)});
}

int	init_canvas(t_all *all, t_canvas *canvas)
{
	int	i;

	if (init_canvas_utils(all, canvas))
		return (1);
	i = -1;
	while (++i < all->win_height)
	{
		canvas->rays[i] = malloc((all->win_width) * sizeof(t_ray));
		if (!canvas->rays[i])
			return (1);
		canvas->rays_save[i] = malloc((all->win_width) * sizeof(t_vec));
		if (!canvas->rays_save[i])
			return (1);
		canvas->gradient[i] = get_background_color(all->win_height, i);
	}
	return (0);
}

	//print_all_structs(all);

int	__init__(t_all *all, char **argv, int argc)
{
	ft_zeroes(all);
	all->argv = argv;
	all->argc = argc;
	if (check_ext(all->argv) || __parse_file_scene(all))
		return (1);
	if (all->ambient_light.nb <= 0)
		return (printf("Error: you must have 1 ambient light\n"), 1);
	if (all->camera.nb <= 0)
		return (printf("Error: you must have 1 camera\n"), 1);
	if (__parse_file_objs(all))
		return (1);
	if (init_canvas(all, &all->canvas))
		return (1);
	apply_rgb_all_shape(all);
	all->nb_items = all->nb_shapes + get_depth_objs(all->objects);
	create_shape_array(all);
	sort_shape(all->shapes);
	all->bvh = create_bvh_iter(all, all->nb_shapes, 0);
	if (!all->bvh)
		return (1);
	if (all->bvh->node_type != LEAF)
		all->bvh->node_type = ROOT;
	make_perpendicular(&all->camera);
	cal_fov(all);
	return (0);
}
