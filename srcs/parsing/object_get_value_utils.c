#include "miniRT.h"

int	get_vertices(t_vertice *vertice, char **s, unsigned long *index)
{
	if (skip_till_number(s, 1))
		return (free(vertice), 3);
	vertice->x = ft_atof(s);
	if (ft_iswhitespace(*(++(*s))))
		return (printf(ERROR_X_DECODE, *((*s) - 1), *((*s) - 1)), 1);
	if (skip_till_number(s, 0))
		return (3);
	vertice->y = ft_atof(s);
	if (ft_iswhitespace(*(++(*s))))
		return (printf(ERROR_Y_DECODE, *((*s) - 1), *((*s) - 1)), 1);
	if (skip_till_number(s, 0))
		return (3);
	vertice->z = ft_atof(s);
	if (**s && !ft_iswhitespace(**s))
		return (printf(ERROR_Z_DECODE, **s, **s), 1);
	(*index)++;
	if (!**s)
		return (2);
	return (skip_whitespace_hashtag_u(s, &(__get_head(NULL)->line_count)));
}

int	get_smoothing(t_minuint *curr_smoothing, char **s)
{
	(void)skip_till_number(s, 1);
	if ((**s != 'o' && **s != 'O') && !(**s >= '0' && **s <= '9'))
		return (3);
	*curr_smoothing = ft_atoi(s);
	if (**s && !ft_iswhitespace(**s))
	{
		if (ft_strncmp(*s, "off", 3) && !ft_iswhitespace(**s))
			return (printf("Error decoding smoothing @: [%d|%c]\n", **s, **s), 1);
		*s += 3;
		*curr_smoothing = 0;
	}
	if (!**s)
		return (2);
	return (skip_whitespace_hashtag_u(s, &(__get_head(NULL)->line_count)));
}

int	get_faces(t_face *face, char **s, t_minuint curr_smoothing, unsigned long *index)
{
	if (skip_till_number(s, 1))
		return (free(face), 3);
	face->p_one = ft_atoi(s);
	if (ft_iswhitespace(*(++(*s))))
		return (printf(ERROR_X_DECODE, *((*s) - 1), *((*s) - 1)), 1);
	if (skip_till_number(s, 0))
		return (3);
	face->p_two = ft_atoi(s);
	if (ft_iswhitespace(*(++(*s))))
		return (printf(ERROR_Y_DECODE, *((*s) - 1), *((*s) - 1)), 1);
	if (skip_till_number(s, 0))
		return (3);
	face->p_three = ft_atoi(s);
	if (**s && !ft_iswhitespace(**s))
		return (printf(ERROR_Z_DECODE, **s, **s), 1);
	face->smoothing = curr_smoothing;
	(*index)++;
	if (!**s)
		return (2);
	return (skip_whitespace_hashtag_u(s, &(__get_head(NULL)->line_count)));
}

int get_name(char name[128], char **s)
{
	int	i;

	i = 0;
	if (!skip_till_number(s, 2))
		return (3);
	while (**s && **s != '\n' && i < 128)
	{
		name[i++] = **s;
		(*s)++;
	}
	name[i] = 0;
	printf("name: [%s]\n", name);
	if (!**s)
		return (2);
	return (skip_whitespace_hashtag_u(s, &(__get_head(NULL)->line_count)));
}

int	get_letters(t_object *object, const char *restrict s)
{
	while (*s)
	{
		object->nb_faces += (*s == 'f');
		object->nb_vertices += (*s == 'v');
		object->nb_points += (*s == 'p');
		s++;
		while (*s && *s != '\n')
			s++;
		while (ft_iswhitespace(*s) || *s == '#')
		{
			if (*s == '#')
				while (*s && *s != '\n')
					(s)++;
			else
				(s)++;
		}
	}
	if (!object->nb_vertices)
		return (printf("Error: Cannot have empty vertexes\n"), 1);
	if (object->nb_vertices < 2 && object->nb_faces >= 1)
		return (printf("Error: Cannot have a face without 3 vertexes\n"),1);
	printf("v[%lu] f[%lu] p[%lu]\n", object->nb_vertices, object->nb_faces, object->nb_points);
	return (0);
}