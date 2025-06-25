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

static int get_each_part_face(t_face *face, char **s, unsigned char ind[3])
{
	unsigned long	tmp;
	
	if (!(**s >= '0' && **s <= '9'))
		return (3);
	tmp = ft_atoi(s);
	if (tmp <= 0)
		return (printf("Error: Number cannot be less than 1\n"), --(*s), 3);
	if (tmp > __get_head(NULL)->nb_vertices)
		return (printf("Error: Number cannot more than %ld\n",
			__get_head(NULL)->nb_vertices), --(*s), 3);
	tmp -= 1;
	face->vertices[ind[0]] = &(__get_head(NULL)->vertices[tmp]);
	face->v_indexes[ind[0]] = tmp;
	ind[0] += 1;
	if (skip_till_number(s, 0) && (**s >= '0' && **s <= '9'))
		return (3);
	if (ind[0] == 3 && (**s >= '0' && **s <= '9'))
			return (4);
	return (0);
}

int count_duplicates(void *arr[4])
{
	if (!arr[3])
		return (((arr[0] == arr[1]) + (arr[0] == arr[2]) + (arr[1] == arr[2])) >= 1);
	else
		return (((arr[0] == arr[1]) + (arr[0] == arr[2]) + (arr[0] == arr[3]) +
				(arr[1] == arr[2]) + (arr[1] == arr[3]) + (arr[2] == arr[3])) >= 2);
}

int	get_faces(t_face *face, char **s, t_minuint curr_smoothing, unsigned long *index)
{
	unsigned char vert_ind[3];
	int	err;
	int	i;

	err = 0;
	i = 0;
	ft_memset(vert_ind, 0, sizeof(vert_ind));
	ft_memset(face->vertices, 0, sizeof(face->vertices));
	if (skip_till_number(s, 1) && (**s >= '0' && **s <= '9'))
		return (free(face), 3);
	while (i < 3)
	{
		err = get_each_part_face(face, s, vert_ind);
		if (err && err != 4)
			return (err);
		if (i == 2 && err == 4)
			break ; 
		i++;
	}
	if (err == 4)
		err = get_each_part_face(face, s, vert_ind);
	if (err)
		return (err);
	face->is_wrong = count_duplicates((void *)face->vertices);
	face->smoothing = curr_smoothing;
	(*index)++;
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
	return (skip_whitespace_hashtag_u(s, &(__get_head(NULL)->line_count)));
}

int	get_letters(t_object *object, const char *restrict s)
{
	while (*s)
	{
		object->nb_faces += (*s == 'f' && *(s + 1) == ' ');
		object->nb_vertices += (*s == 'v' && *(s + 1) == ' ');
		object->nb_points += (*s == 'p' && *(s + 1) == ' ');
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
	return (0);
}
