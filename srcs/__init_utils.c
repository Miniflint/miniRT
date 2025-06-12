#include "miniRT.h"

static int	parse_type(t_all *all, char **s)
{
    if (**s == 'A' && ft_iswhitespace(*((*s) + 1)))
		return (get_ambient_light(&all->ambient_light, s));
	else if (**s == 'C' && ft_iswhitespace(*((*s) + 1)))
		return ((t_obj_type)CAMERA);
	else if (**s == 'L' && ft_iswhitespace(*((*s) + 1)))
		return ((t_obj_type)LIGHT);
	else if (**s == 's' && *((*s) + 1) == 'p' && ft_iswhitespace(*((*s) + 2)))
		return ((t_obj_type)SPHERE);
	else if (**s == 'p' && *((*s) + 1) == 'l' && ft_iswhitespace(*((*s) + 2)))
		return ((t_obj_type)PLANE);
	else if (**s == 'c' && *((*s) + 1) == 'y' && ft_iswhitespace(*((*s) + 2)))
		return ((t_obj_type)CYLINDER);
    return (1);
}

int	__set_values(t_all *all, char **s)
{
    int err;

    skip_whitespace_hashtag(s);
    err = 0;
    while (err != 2)
    {
        err = parse_type(all, s);
        if (err == 1)
            return (err);
    }
    return (0);
}