#include "miniRT.h"

t_vec	*cross_product(t_vec *a, t_vec *b, t_vec *c)
{
	c->x = (a->y * b->z) - (a->z * b->y);
	c->y = (a->z * b->x) - (a->x * b->z);
	c->z = (a->x * b->y) - (a->y * b->x);
	return (c);
}

void	make_perpendicular(t_cam *cam)
{
	t_vec	ideal_up;
	double	mag;

	ideal_up = (t_vec){.x = 0, .y = 0, .z = 1};
	if (fabs(dot_product(&cam->dir, &ideal_up)) > 0.9999f)
		ideal_up = (t_vec){.x = 0, .y = 1, .z = 0};
	cross_product(&cam->dir, &ideal_up, &cam->dir_x);
	mag = dot_product(&cam->dir_x, &cam->dir_x);
	norm_vectors(&cam->dir_x, mag, &cam->dir_x);
	cross_product(&cam->dir, &cam->dir_x, &cam->dir_y);
	mag = dot_product(&cam->dir_y, &cam->dir_y);
	norm_vectors(&cam->dir_y, mag, &cam->dir_y);
}
