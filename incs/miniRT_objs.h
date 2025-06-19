#ifndef MINIRT_OBJS_H
# define MINIRT_OBJS_H

# include "miniRT.h"

typedef struct	S_vertex
{
	double	x;
	double	y;
	double	z;
	int		s;
}				t_vertex;

typedef struct S_face
{
	long	p_one;
	long	p_two;
	long	p_three;
}				t_face;

typedef struct S_object
{
	t_vertex	*vertexes;
	t_face		*faces;
}	t_object;

#endif