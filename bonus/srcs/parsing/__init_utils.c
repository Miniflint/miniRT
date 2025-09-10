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
		return (all->nb_shapes++, get_sphere(&all->spheres, s));
	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
		return (get_plane(&all->planes, s));
	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
		return (all->nb_shapes++, get_cylinder(&all->cylinders, s));
	else if (**s == 'b' && *((*s) + 1) == 'x' && ft_iswhitespace(*((*s) + 2)))
		return (all->nb_shapes++, get_box(&all->boxes, s));
	else if (**s == 'o' && *((*s) + 1) == 'b' && ft_iswhitespace(*((*s) + 2)))
		return (all->nb_shapes++, get_obj(&all->objects, s));
	return (3);
}

void	print_all_structs(t_all *all)
{
	print_ac(&all->ambient_light, &all->camera);
	print_l(all->lights, 0);
	print_sp(all->spheres, 0);
	print_pl(all->planes, 0);
	print_cy(all->cylinders, 0);
	print_bx(all->boxes, 0);
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
