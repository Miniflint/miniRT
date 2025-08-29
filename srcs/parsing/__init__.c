#include "miniRT.h"

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
	all->canvas.pixel_values = 1;
	all->light_ratio = 1;
	all->distance_light = DISTANCE_LIGHT_MIDDLE * DISTANCE_LIGHT_MIDDLE;
}

static int	__parse_file_scene(t_all *all)
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

static int	__parse_file_objs(t_all *all)
{
	int		i;

	i = 2;
	while (i < all->argc)
	{
		all->objects = create_obj_path(&all->objects, all->argv[i]);
		if (!all->objects)
			return (1);
		i++;
	}
	return (0);
}

static int	check_ext(char **argv)
{
	int			i;
	const char	exts[2][5] = {".rt", ".obj"};
	int			max_len_str;
	int			max_len_ext;

	i = 1;
	while (argv[i])
	{
		max_len_str = ft_strlen(argv[i]);
		max_len_ext = ft_strlen((char *)exts[i > 1]);
		if (max_len_ext > max_len_str)
			return (printf("Error: extension doesn't match: %s\n",
					exts[i > 1]), 1);
		while (max_len_ext > 0 && max_len_str > 0
			&& argv[i][max_len_str] == exts[i > 1][max_len_ext])
		{
			max_len_str--;
			max_len_ext--;
		}
		if (argv[i][max_len_str] != exts[i > 1][max_len_ext])
			return (printf("Extension doesn't match %s\n", exts[i > 1]), 1);
		i++;
	}
	return (0);
}

void	apply_argb_save_rgb(t_rgb *rgb_save, t_rgb_f ambient_rgb, t_rgb *into)
{
	into->r = (double)rgb_save->r * ambient_rgb.r;
	into->g = (double)rgb_save->g * ambient_rgb.g;
	into->b = (double)rgb_save->b * ambient_rgb.b;
}

void	apply_rgb_all_shape(t_all *all)
{
	const t_sphere		*tmp_sp = all->spheres;
	const t_plane		*tmp_pl = all->planes;
	const t_cylinder	*tmp_cy = all->cylinders;
	const t_rgb_f		r = all->ambient_light.rgb_norm;

	while (all->spheres)
	{
		apply_argb_save_rgb(&all->spheres->rgb_save, r, &all->spheres->rgb);
		all->spheres = all->spheres->next;
	}
	all->spheres = (t_sphere *)tmp_sp;
	while (all->planes)
	{
		apply_argb_save_rgb(&all->planes->rgb_save, r, &all->planes->rgb);
		all->planes = all->planes->next;
	}
	all->planes = (t_plane *)tmp_pl;
	while (all->cylinders)
	{
		apply_argb_save_rgb(&all->cylinders->rgb_save, r, &all->cylinders->rgb);
		all->cylinders = all->cylinders->next;
	}
	all->cylinders = (t_cylinder *)tmp_cy;
}

int	__init__(t_all *all, char **argv, int argc)
{
	ft_zeroes(all);
	all->argv = argv;
	all->argc = argc;
	if (check_ext(all->argv))
		return (1);
	if (__parse_file_scene(all))
		return (1);
	if (all->ambient_light.nb <= 0)
		return (printf("Error: you must have 1 ambient light\n"), 1);
	if (all->camera.nb <= 0)
		return (printf("Error: you must have 1 camera\n"), 1);
	apply_rgb_all_shape(all);
	if (__parse_file_objs(all))
		return (1);
	print_all_structs(all);
	norm_vectors(&all->camera.dir,
		vec_magnitude(&all->camera.dir), &all->camera.dir);
	make_perpendicular(&all->camera);
	cal_fov(all);
	return (0);
}
