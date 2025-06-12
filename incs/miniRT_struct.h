#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

# include "miniRT.h"

typedef unsigned char	t_minuint;

typedef struct S_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef struct S_vector
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct S_rgb
{
	t_minuint	r;
	t_minuint	g;
	t_minuint	b;
}	t_rgb;

#endif