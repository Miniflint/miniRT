#ifndef MINIRT_PLANES_H
# define MINIRT_PLANES_H

# include "miniRT.h"

typedef struct S_material	t_material;

typedef struct S_ambient_light
{
	t_minuint	nb;
	double		ratio;
	t_rgb		rgb;
	t_rgb_f		rgb_norm;
}	t_amb_light;

typedef struct S_camera
{
	t_minuint	nb;
	t_coord		viewpoint;
	t_vec		dir;
	t_vec		dir_x;
	t_vec		dir_y;
	double		fov;
}	t_cam;

typedef struct S_light
{
	t_coord			coord;
	double			ratio;
	t_rgb			rgb;
	t_rgb_f			rgb_norm;
	struct S_light	*next;
}	t_light;

typedef struct S_sphere
{
	t_coord			coord;
	double			radius;
	double			radius_squared;
	double			diameter;
	t_rgb			rgb;
	t_rgb_f			color;
	t_rgb			rgb_save;
	t_material		material;
	struct S_sphere	*next;
}	t_sphere;

typedef struct S_plane
{
	t_coord			coord;
	t_vec			vec;
	t_rgb			rgb;
	t_rgb_f			color;
	t_rgb			rgb_save;
	t_material		material;
	struct S_plane	*next;
}	t_plane;

typedef struct S_cylinder
{
	t_coord				coord;
	t_vec				vec;
	double				radius;
	double				radius_squared;
	double				diameter;
	double				height;
	t_rgb				rgb;
	t_rgb_f				color;
	t_rgb				rgb_save;
		t_material		material;
	struct S_cylinder	*next;
}	t_cylinder;

typedef struct S_box
{
	t_bvh			box;
	t_rgb			rgb;
	t_rgb			rgb_save;
	t_rgb_f			color;
	t_material		material;
	struct S_box	*next;
}	t_box;

#endif
