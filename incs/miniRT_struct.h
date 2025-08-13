#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

# include "miniRT.h"
# include "tri_colors.h"

#define ERROR_X_DECODE "Error decoding (X)YZ coordinates @: [%d|%c]\nline [%lu]\n"
#define ERROR_Y_DECODE "Error decoding X(Y)Z coordinates @: [%d|%c]\nline [%lu]\n"
#define ERROR_Z_DECODE "Error decoding XY(Z) coordinates @: [%d|%c]\nline [%lu]\n"

#define ERROR_R_DECODE "Error decoding (R)GB color @: [%d|%c]\nline [%lu]\n"
#define ERROR_G_DECODE "Error decoding R(G)B color @: [%d|%c]\nline [%lu]\n"
#define ERROR_B_DECODE "Error decoding RG(B) color @: [%d|%c]\nline [%lu]\n"

typedef struct S_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef unsigned char	t_minuint;
typedef t_coord			t_vec;
typedef t_argb			t_rgb;

// typedef struct S_rgb
// {
// 	t_minuint	r;
// 	t_minuint	g;
// 	t_minuint	b;
// }	t_rgb;

typedef enum E_obj_type
{
	AMBIENT_LIGHT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

typedef struct S_ray
{
	t_coord	start;
	t_vec	dir;
	t_argb	color;
}	t_ray;

typedef struct S_Canvas
{
	double			size_x;
	double			size_y;
	double			unit;
	t_minuint		pixel_values;
	double			pix_x[WIN_WIDTH_ALL];
	double			pix_y[WIN_HEIGHT_ALL];
	t_ray			rays[WIN_HEIGHT_ALL][WIN_WIDTH_ALL];
}	t_canvas;	

#endif