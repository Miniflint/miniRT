#include "miniRT.h"
#include <stdint.h>

int	get_vertices(
	t_vertice *vertice,
	char **const restrict s,
	int skip,
	unsigned long *index
)
{
	if (skip_till_number(s, skip))
		return (free(vertice), 3);
	vertice->x = ft_atof(s);
	if (ft_iswhitespace(*(++(*s))))
		return (printf(ERROR_X_DECODE, *((*s) - 1),
				*((*s) - 1), __get_head(NULL)->line_count), 1);
	if (skip_till_number(s, 0))
		return (3);
	vertice->y = ft_atof(s);
	if (ft_iswhitespace(*(++(*s))))
		return (printf(ERROR_Y_DECODE, *((*s) - 1),
				*((*s) - 1), __get_head(NULL)->line_count), 1);
	if (skip_till_number(s, 0))
		return (3);
	vertice->z = ft_atof(s);
	if (**s && !ft_iswhitespace(**s))
		return (printf(ERROR_Z_DECODE,
				**s, **s, __get_head(NULL)->line_count), 1);
	if (!**s)
		return (2);
	(*index)++;
	return (skip_whitespace_hashtag(s, &(__get_head(NULL)->line_count)));
}

int	get_smoothing(t_minuint *curr_smoothing, char **const restrict s)
{
	unsigned int	tmp;

	(void)skip_till_number(s, 1);
	if ((**s != 'o' && **s != 'O') && !(**s >= '0' && **s <= '9'))
		return (3);
	tmp = ft_atoi(s);
	if (tmp > 255)
		return (printf("Smoothing cannot exceed 255\n"), (*s)--, 3);
	if (**s && !ft_iswhitespace(**s))
	{
		if (ft_strncmp(*s, "off", 3) && !ft_iswhitespace(**s))
			return (printf("Error decoding smoothing @: [%d|%c]\nline [%lu]\n",
					**s, **s, __get_head(NULL)->line_count), 1);
		*s += 3;
		tmp = 0;
	}
	if (!**s)
		return (2);
	*curr_smoothing = (tmp & 0xFF);
	return (skip_whitespace_hashtag(s, &(__get_head(NULL)->line_count)));
}

void	set_face_value_on_slash(t_face *face,
	unsigned long tmp,
	unsigned char slashes,
	unsigned char ind[3])
{
	if (slashes == 0)
	{
		face->vertices[ind[slashes]] = &(__get_head(NULL)->vertices[tmp]);
		face->v_indexes[ind[slashes]] = tmp;
	}
	else if (slashes == 1)
	{
		face->v_texture[ind[slashes]] = &(__get_head(NULL)->vt[tmp]);
		face->vt_indexes[ind[slashes]] = tmp;
	}
	else if (slashes == 2)
	{
		face->v_normale[ind[slashes]] = &(__get_head(NULL)->vn[tmp]);
		face->vn_indexes[ind[slashes]] = tmp;
	}
	ind[slashes] += 1;
}

static int	set_tmp(
	unsigned long *tmp,
	unsigned char slashes,
	char **const restrict s
)
{
	if (!(**s >= '0' && **s <= '9'))
		return (3);
	*tmp = ft_atoi(s);
	if (*tmp <= 0)
		return (printf("Error: Number cannot be less than 1\n"), --(*s), 3);
	if (slashes == 0 && *tmp > __get_head(NULL)->nb_vertices)
		return (printf("Error: Number cannot more than %ld\n",
				__get_head(NULL)->nb_vertices), --(*s), 3);
	else if (slashes == 1 && *tmp > __get_head(NULL)->nb_vt)
		return (printf("Error: Number cannot more than %ld\n",
				__get_head(NULL)->nb_vt), --(*s), 3);
	else if (slashes == 2 && *tmp > __get_head(NULL)->nb_vn)
		return (printf("Error: Number cannot more than %ld\n",
				__get_head(NULL)->nb_vn), --(*s), 3);
	*tmp = *tmp - 1;
	return (0);
}

static void	norminette_fck_u(
	unsigned char	*slashes,
	char **const restrict s
)
{
	while (**s == '/')
	{
		*slashes += 1;
		(*s)++;
	}
}

static int	get_each_part_face(
	t_face *face,
	char **const restrict s,
	unsigned char ind[3]
)
{
	unsigned long	tmp;
	int				rtn;
	unsigned char	slashes;

	slashes = 0;
	while (slashes <= 2)
	{
		rtn = set_tmp(&tmp, slashes, s);
		if (rtn)
			return (rtn);
		set_face_value_on_slash(face, tmp, slashes, ind);
		if (**s == '/')
			norminette_fck_u(&slashes, s);
		else
			break ;
	}
	if (skip_till_number(s, 0) && (**s >= '0' && **s <= '9'))
		return (3);
	if (ind[0] == 3 && (**s >= '0' && **s <= '9'))
		return (4);
	return (0);
}

int	count_duplicates(void *arr[4])
{
	if (!arr[3])
		return (
			(
				(arr[0] == arr[1]) + (arr[0] == arr[2]) + (arr[1] == arr[2])
			) > 0);
	else
		return (
			(
				(arr[0] == arr[1]) + (arr[0] == arr[2]) + (arr[0] == arr[3])
				+ (arr[1] == arr[2]) + (arr[1] == arr[3]) + (arr[2] == arr[3])
			) > 1);
}

void	__init_faces(t_face *face, unsigned char vert_ind[3], int *err, int *i)
{
	*err = 0;
	*i = -1;
	ft_memset(vert_ind, 0, sizeof(vert_ind[0]));
	ft_memset(face->vertices, 0, sizeof(face->vertices));
	ft_memset(face->v_texture, 0, sizeof(face->v_texture));
	ft_memset(face->v_normale, 0, sizeof(face->v_normale));
	ft_memset(face->v_indexes, 0, sizeof(face->v_indexes));
	ft_memset(face->vt_indexes, 0, sizeof(face->vt_indexes));
	ft_memset(face->vn_indexes, 0, sizeof(face->vn_indexes));
}

int	set_face_parts(
	t_face *face,
	char **const restrict s,
	unsigned char vert_ind[3]
)
{
	int	i;
	int	err;

	i = 0;
	while (i < 3)
	{
		err = get_each_part_face(face, s, vert_ind);
		if (i == 2 && err == 4)
			break ;
		if (err && err != 4)
			return (err);
		i++;
	}
	if (err == 4)
		err = get_each_part_face(face, s, vert_ind);
	if (err)
		return (err);
	return (0);
}

int	get_faces(t_face *face,
	char **const restrict s,
	t_minuint curr_smoothing,
	unsigned long *index
)
{
	unsigned char	vert_ind[3];
	int				i;
	int				err;
	const t_object	*obj = __get_head(NULL);

	__init_faces(face, vert_ind, &err, &i);
	while (obj->curr_group[++i])
		face->group[i] = obj->curr_group[i];
	face->group[i] = 0;
	if (skip_till_number(s, 1) && (**s >= '0' && **s <= '9'))
		return (free(face), 3);
	err = set_face_parts(face, s, vert_ind);
	if (err)
		return (err);
	face->is_wrong = count_duplicates((void *)face->vertices);
	face->smoothing = curr_smoothing;
	(*index)++;
	return (skip_whitespace_hashtag(s, &((t_object *)obj)->line_count));
}

int	get_name(char name[128], char **const restrict s)
{
	int	i;

	i = 0;
	(void)skip_till_number(s, 1);
	while (**s && **s != '\n' && i < 127)
	{
		name[i++] = **s;
		(*s)++;
	}
	name[i] = 0;
	if (!i)
		return ((*s)++, skip_whitespace_hashtag(
				s, &(__get_head(NULL)->line_count)), 0);
	return (skip_whitespace_hashtag(s, &(__get_head(NULL)->line_count)));
}

void	ifs(t_object *object, const char *restrict s)
{
	if (*s == 'f' && *(s + 1) == ' ')
		object->nb_faces += 1;
	else if (*s == 'v' && *(s + 1) == 't' && *(s + 2) == ' ')
		object->nb_vt += 1;
	else if (*s == 'v' && *(s + 1) == 'n' && *(s + 2) == ' ')
		object->nb_vn += 1;
	else if (*s == 'v' && *(s + 1) == ' ')
		object->nb_vertices += 1;
	else if (*s == 'p' && *(s + 1) == ' ')
		object->nb_points += 1;
}

int	get_letters(t_object *object, const char *restrict s)
{
	while (*s)
	{
		ifs(object, s);
		s++;
		while (*s && *s != '\n')
			s++;
		while (ft_iswhitespace(*s) || *s == '#')
		{
			if (*s == '#')
				while (*s && *s != '\n')
					s++;
			else
				s++;
		}
	}
	if (!object->nb_vertices)
		return (printf("Error: Cannot have empty vertices\n"), 1);
	if (object->nb_vertices < 2 && object->nb_faces >= 1)
		return (printf("Error: Cannot have a face without 3 vertexes\n"), 1);
	printf("v[%ld] vt[%ld] vn[%ld] f[%ld] p[%ld]\n",
		object->nb_vertices, object->nb_vt, object->nb_vn,
		object->nb_faces, object->nb_points);
	return (0);
}

int	get_obj(t_object **head, char **const restrict s)
{
	int		i;
	char	name[256];

	i = 0;
	if (!skip_till_number(s, 2) && **s != '"')
		return (3);
	(*s)++;
	while (**s && **s != '"' && i < 255)
	{
		if (**s == '\n')
			return (3);
		name[i++] = *((*s)++);
	}
	name[i] = 0;
	if (!i)
		return (printf("file path cannot be empty\n"), 3);
	if (!create_obj_path(head, &name[0]))
		return (1);
	if (skip_till_number(s, 1))
		return (3);
	if (get_coord(&((*head)->coord), s))
		return (1);
	if (!**s)
		return (2);
	return (skip_whitespace_hashtag(s, &(__get_all()->line_count)));
}
