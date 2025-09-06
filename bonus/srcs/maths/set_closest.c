#include "miniRT.h"

void	set_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	cylinder->v = scalar_multiplication_no_v(&cylinder->vec, cylinder->mag);
	cylinder->normal = sub_vectors_no_v(&cylinder->p, &cylinder->v);
	cylinder->normal_mag = vec_magnitude(&cylinder->normal);
	ray->shape.origin = cylinder->coord;
	ray->shape.normal = cylinder->normal;
	norm_vectors(&ray->shape.normal,
		cylinder->normal_mag, &ray->shape.normal);
	ray->color_shape = cylinder->color;
}

void	set_shapes(t_ray *ray)
{
	if (ray->shape.type == SPHERE)
	{
		ray->shape.origin = ((t_sphere *)(ray->shape.shape))->coord;
		sub_vectors(&ray->hit, &ray->shape.origin, &ray->shape.normal);
		norm_vectors(&ray->shape.normal,
			vec_magnitude(&ray->shape.normal), &ray->shape.normal);
		ray->color_shape = ((t_sphere *)(ray->shape.shape))->color;
	}
	else if (ray->shape.type == PLANE)
	{
		ray->shape.origin = ((t_plane *)(ray->shape.shape))->coord;
		ray->shape.normal = ((t_plane *)(ray->shape.shape))->vec;
		ray->color_shape = ((t_plane *)(ray->shape.shape))->color;
	}
	else if (ray->shape.type == CYLINDER)
		set_cylinder(ray, (t_cylinder *)ray->shape.shape);
}
