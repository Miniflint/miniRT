#ifndef MINIRT_PLANES_H
# define MINIRT_PLANES_H

# include "miniRT.h"

typedef struct S_ambient_light
{
	t_minuint	nb;
	double		ratio;
	t_rgb		rgb;
}	t_amb_light;

typedef struct S_camera
{
	t_minuint	nb;
	t_coord		viewpoint;
	t_vec		vec;
	t_minuint	fov;
}	t_cam;

typedef struct S_light
{
	t_coord			coord;
	double			ratio;
	t_rgb			rgb;
	struct S_light	*next;
}	t_light;

typedef struct S_sphere
{
	t_coord			coord;
	float			diameter;
	t_rgb			rgb;
	struct S_sphere	*next;
}	t_sphere;

typedef struct S_plane
{
	t_coord			coord;
	t_vec			vec;
	t_rgb			rgb;
	struct S_plane	*next;
}	t_plane;

typedef struct S_cylinder
{
	t_coord				coord;
	t_vec				vec;
	double				diameter;
	double				height;
	t_rgb				rgb;
	struct S_cylinder	*next;
}	t_cylinder;

#endif
