/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_get_value_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:05:40 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:06:18 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdint.h>

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
