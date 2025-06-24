#ifndef MINIRT_OBJS_H
# define MINIRT_OBJS_H

# include "miniRT.h"


typedef struct	S_vertex
{
	double	x;
	double	y;
	double	z;
}				t_vertex;

typedef struct S_point
{
	unsigned long	value;
	struct S_point	*next;
}	t_point;

typedef struct S_face
{
	long		p_one;
	long		p_two;
	long		p_three;
	t_minuint	smoothing;
}				t_face;

typedef struct S_object
{
	char			name[128];
	char			*path;
	t_vertex		*vertexes;
	t_face			*faces;
	t_point			*points;
	t_minuint		curr_smoothing;
	unsigned long	line_count;
	unsigned long	nb_vertexes;
	unsigned long	nb_faces;
	unsigned long	nb_points;
	struct S_object	*next;

}	t_object;

#endif