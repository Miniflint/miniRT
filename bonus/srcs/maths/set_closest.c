#include "miniRT.h"

void	set_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	ray->shape.cyl_v = scalar_multiplication_no_v(&cylinder->vec, ray->shape.cyl_mag);
	ray->shape.cyl_normal = sub_vectors_no_v(&ray->shape.cyl_p, &ray->shape.cyl_v);
	ray->shape.cyl_normal_mag = vec_magnitude(&ray->shape.cyl_normal);
	ray->shape.origin = cylinder->coord;
	ray->shape.normal = ray->shape.cyl_normal;
	norm_vectors(&ray->shape.normal,
		ray->shape.cyl_normal_mag, &ray->shape.normal);
	ray->color_shape = cylinder->color;
	ray->shape.material = cylinder->material;
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
		ray->shape.material = ((t_sphere *)(ray->shape.shape))->material;
	}
	else if (ray->shape.type == PLANE)
	{
		//ray->shape.origin = ((t_plane *)(ray->shape.shape))->coord;
		ray->shape.normal = ((t_plane *)(ray->shape.shape))->vec;
		ray->color_shape = ((t_plane *)(ray->shape.shape))->color;
		ray->shape.material = ((t_plane *)(ray->shape.shape))->material;
	}
	else if (ray->shape.type == CYLINDER)
		set_cylinder(ray, (t_cylinder *)ray->shape.shape);
	else if (ray->shape.type == BOX)
	{
		ray->color_shape = ((t_box *)(ray->shape.shape))->color;
		ray->shape.material = ((t_box *)(ray->shape.shape))->material;
	}
	else if (ray->shape.type == TRIANGLE)
	{
		//ray->shape.normal = cross_product(&edge1, &edge2, &normal);
		ray->color_shape =  (t_rgb_f){0.5, 0.5, 0.5};//((t_face *)(ray->shape.shape))->color;
		//ray->shape.material = ((t_face *)(ray->shape.shape))->material;
	}
	ray->shape.material = (t_material){.ks=0.8, .shininess=256, .reflection={0, 0, 0}}; //En attendant le parsing
}
