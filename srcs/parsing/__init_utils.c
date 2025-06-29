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
	else if (**s == 'o' && *((*s) + 1) == 'b' && ft_iswhitespace(*((*s) + 2)))
		return (get_obj(&all->objects, s));
	return (3);
}

int	parse_type_objs(t_object *object, char **s)
{
	if (**s == 'o' && ft_iswhitespace(*((*s) + 1)))
		return (get_name(object->name, s));
	else if (**s == 'v' && ft_iswhitespace(*((*s) + 1)))
		return (get_vertices(&(object->vertices[object->i_vertice[I_V]]), s, 1, &(object->i_vertice[I_V])));
	else if (**s == 'v' && *((*s) + 1) == 't' && ft_iswhitespace(*((*s) + 2)))
		return (get_vertices(&(object->vt[object->i_vertice[I_VT]]), s, 2, &(object->i_vertice[I_VT])));
	else if (**s == 'v' && *((*s) + 1) == 'n' && ft_iswhitespace(*((*s) + 2)))
		return (get_vertices(&(object->vn[object->i_vertice[I_VN]]), s, 2, &(object->i_vertice[I_VN])));
	else if (**s == 'f' && ft_iswhitespace(*((*s) + 1)))
		return (get_faces(&(object->faces[object->indexes[I_FACES]]), s, object->curr_smoothing, &(object->indexes[I_FACES])));
	else if (**s == 's' && ft_iswhitespace(*((*s) + 1)))
		return (get_smoothing(&object->curr_smoothing, s));
	else if (**s == 'g' && ft_iswhitespace(*((*s) + 1)))
		return (get_name(object->curr_group, s));
	//else if (**s == 'p' && ft_iswhitespace(*((*s) + 1)))
	//	 return ((&all->planes, s));
	return (3);
}

void	print_all_structs(t_all *all)
{
	print_ac(&all->ambient_light, &all->camera);
	print_l(all->lights, 0);
	print_sp(all->spheres, 0);
	print_pl(all->planes, 0);
	print_cy(all->cylinders, 0);
	print_ob(all->objects, 0);
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
			return (printf("Unwanted character: ['%c'] in line: [%lu]\n",
				**s, all->line_count), 1);
	}
	return (0);
}

int	__mallocate_objs_values(t_object *object, char *s)
{
	if (get_letters(object, s))
		return (1);
	if (object->nb_vertices)
		object->vertices = malloc(sizeof(t_vertice) * (object->nb_vertices));
	if (object->nb_vertices && !object->vertices)
		return (printf("malloc error - vertices\n"), 1);
	if (object->nb_vt)
		object->vt = malloc(sizeof(t_vertice_t) * (object->nb_vt));
	if (object->nb_vt && !object->vt)
		return (printf("malloc error - vertices texture\n"), 1);
	if (object->nb_vn)
		object->vn = malloc(sizeof(t_vertice_n) * (object->nb_vn));
	if (object->nb_vn && !object->vn)
		return (printf("malloc error - vertices normale\n"), 1);
	if (object->nb_faces)
		object->faces = malloc(sizeof(t_face) * (object->nb_faces));
	if (object->nb_faces && !object->faces)
		return (printf("malloc error - faces\n"), 1);
	if (object->nb_points)
		object->points = malloc(sizeof(t_point) * (object->nb_points));
	if (object->nb_points && !object->points)
		return (printf("malloc error - points\n"), 1);
	return (0);
}

t_object	*create_obj_path(t_object **head, char *path)
{
	int			fd;
	char		*str;
	char		*tmp;
	t_object	*object;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (printf("File cannot be accessed\n"), NULL);
	str = readfile(fd);
	if (!str)
		return (printf("File is empty/error occured while trying to read\n"), NULL);
	tmp = str;
	object = (t_object *)create_empty_node(sizeof(t_object) * 1);
	if (!object)
		return (printf("malloc error\n"), NULL);
	zeroes_two(object, path);
	(void)__get_head(object);
	if (__set_values_objs(object, &str))
		return (free(tmp), NULL);
	free(tmp);
	object->next = *head;
	*head = object;
	return (*head);
}

int	__set_values_objs(t_object *object, char **s)
{
	int	err;

	skip_whitespace_hashtag(s, &(object->line_count));
	__mallocate_objs_values(object, *s);
	err = 0;
	while (err != 2)
	{
		err = parse_type_objs(object, s);
		if (err == 1)
			return (err);
		else if (err == 3)
			return (printf("Unwanted character: ['%c'] in line: [%lu]\n",
				**s, object->line_count), 1);
	}
	return (0);
}
