#include "miniRT.h"

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

int	set_tmp(
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

int	get_each_part_face(
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
