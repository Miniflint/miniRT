#include "miniRT.h"

int	parse_type_scene(t_all *all, char **s)
{
	if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
		return (get_ambient_light(&all->ambient_light, s));
	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
		return (get_camera(&all->camera, s));
	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
		return (get_light(&all->lights, s));
	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
		return (get_sphere(&all->spheres, s));
	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
		return (get_plane(&all->planes, s));
	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
		return (get_cylinder(&all->cylinders, s));
	return (3);
}

int	parse_type_objs(t_object *object, char **s)
{
	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
		return (get_name(object->name, s));
	//else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
	//	return (get_camera(&all->camera, s));
	//else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
	//	return (get_light(&all->lights, s));
	//else if (**s == 'g' && ft_iswhitespace(*((*s) + 1)))
	//	return (get_sphere(&all->spheres, s));
	//else if (**s == 'p' && ft_iswhitespace(*((*s) + 1)))
	//	return (get_plane(&all->planes, s));
	return (3);
}

void	print_all_structs(t_all *all)
{
	print_ac(&all->ambient_light, &all->camera);
	print_l(all->lights, 0);
	print_sp(all->spheres, 0);
	print_pl(all->planes, 0);
	print_cy(all->cylinders, 0);
}

int	__set_values_scene(t_all *all, char **s)
{
	int	err;

	skip_whitespace_hashtag(s, &(__get_all()->line_count));
	err = 0;
	while (err != 2 && *s && **s)
	{
		err = parse_type_scene(all, s);
		if (err == 1)
			return (err);
		else if (err == 3)
			return (printf("Error:\nUnwanted character: ['%c'] \
				\nin line: [%u]\n", **s, all->line_count), err);
	}
	return (0);
}

int	__mallocate_objs_values(t_object *object, char *s)
{
	if (get_letters(object, s))
		return (1);
	object->vertexes = malloc(sizeof(t_vertex) * object->nb_vertexes);
	if (!object->vertexes)
		return (printf("malloc error - vertexes\n"), 1);
	object->faces = malloc(sizeof(t_face) * object->nb_faces);
	if (!object->faces)
		return (printf("malloc error - faces\n"), 1);
	object->points = malloc(sizeof(t_point) * object->nb_points);
	if (!object->points)
		return (printf("malloc error - points\n"), 1);
	return (0);
}

int	__set_values_objs(t_object *object, char **s)
{
	int	err;

	skip_whitespace_hashtag_u(s, &(object->line_count));
	__mallocate_objs_values(object, *s);
	err = 0;
	while (err != 2)
	{
		err = parse_type_objs(object, s);
		if (err == 1)
			return (err);
		else if (err == 3)
			return (printf("Error:\nUnwanted character: ['%c'] \
				\nin line: [%lu]\n", **s, object->line_count), err);
	}
	return (0);
}
