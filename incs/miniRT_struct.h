#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

# include "miniRT.h"

#define ERROR_X_DECODE "Error decoding (X)YZ coordinates @: [%d|%c]\n"
#define ERROR_Y_DECODE "Error decoding X(Y)Z coordinates @: [%d|%c]\n"
#define ERROR_Z_DECODE "Error decoding XY(Z) coordinates @: [%d|%c]\n"

#define ERROR_R_DECODE "Error decoding (R)GB color @: [%d|%c]\n"
#define ERROR_G_DECODE "Error decoding R(G)B color @: [%d|%c]\n"
#define ERROR_B_DECODE "Error decoding RG(B) color @: [%d|%c]\n"

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