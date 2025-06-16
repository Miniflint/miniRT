#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

# include "miniRT.h"

typedef struct S_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef unsigned char	t_minuint;
typedef t_coord			t_vec;

typedef struct S_rgb
{
	t_minuint	r;
	t_minuint	g;
	t_minuint	b;
}	t_rgb;

typedef enum E_obj_type
{
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

#endif