/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values_objs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:05:31 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:06:20 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
