#include "miniRT.h"

void	set_cylinder(t_ray *ray, t_cylinder *cylinder, t_threads *thread)
{
	thread->cyl_v
		= scalar_multiplication_no_v(&cylinder->vec, thread->cyl_mag);
	thread->cyl_normal
		= sub_vectors_no_v(&thread->cyl_p, &thread->cyl_v);
	thread->cyl_normal_mag
		= vec_magnitude(&thread->cyl_normal);
	ray->shape.origin = cylinder->coord;
	ray->shape.normal = thread->cyl_normal;
	norm_vectors(&ray->shape.normal,
		thread->cyl_normal_mag, &ray->shape.normal);
	ray->color_shape = cylinder->color;
	ray->shape.material = cylinder->material;
}

void	set_sphere(t_ray *ray, t_sphere *sphere)
{
	ray->shape.origin = sphere->coord;
	sub_vectors(&ray->hit, &ray->shape.origin, &ray->shape.normal);
	norm_vectors(&ray->shape.normal,
		vec_magnitude(&ray->shape.normal), &ray->shape.normal);
	ray->color_shape = sphere->color;
	ray->shape.material = sphere->material;
}

// reminder: put t__material in threads to get object's material
void	set_shapes(t_ray *ray, t_threads *thread)
{
	if (ray->shape.type == SPHERE)
		set_sphere(ray, (t_sphere *)ray->shape.shape);
	else if (ray->shape.type == PLANE)
	{
		ray->shape.normal = ((t_plane *)(ray->shape.shape))->vec;
		ray->color_shape = ((t_plane *)(ray->shape.shape))->color;
		ray->shape.material = ((t_plane *)(ray->shape.shape))->material;
	}
	else if (ray->shape.type == CYLINDER)
		set_cylinder(ray, (t_cylinder *)ray->shape.shape, thread);
	else if (ray->shape.type == BOX)
	{
		ray->color_shape = ((t_box *)(ray->shape.shape))->color;
		ray->shape.material = ((t_box *)(ray->shape.shape))->material;
	}
	else if (ray->shape.type == TRIANGLE)
	{
		ray->color_shape = (t_rgb_f){1, 1, 1};
		ray->shape.material = (t_material){
			.ks = 0.8, .shininess = 256, .reflection = {0.5, 0.5, 0.5}};
	}
}
