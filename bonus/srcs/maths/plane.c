#include "miniRT.h"

// t = n * (r0 - p0) / (n * d)
// t = plane->vec * (ray->start - plane->vec) / plane->vec * ray->dir;

void	intersect_plane(t_ray *ray, t_plane *plane)
{
	double	dot;
	double	t;
	t_vec	new_vec;

	dot = dot_product(&plane->vec, &ray->dir);
	if (dot == 0)
		return ;
	sub_vectors(&ray->start, &plane->coord, &new_vec);
	t = -dot_product(&plane->vec, &new_vec) / dot;
	if (t >= 1e-6 && (isinf(ray->shape.t1) || t < ray->shape.t1))
	{
		ray->shape.t1 = t;
		ray->shape.shape = plane;
		ray->shape.type = PLANE;
	}
}
