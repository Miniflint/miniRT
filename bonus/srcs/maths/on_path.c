#include "miniRT.h"

int	sphere_on_the_path(t_ray *ray, t_sphere *sphere,
		t_vec light_dir, double light_length)
{
	while (sphere)
	{
		if (shadow_intersect_sphere(ray, sphere, light_dir, light_length))
			return (1);
		sphere = sphere->next;
	}
	return (0);
}

int	plane_on_the_path(t_ray *ray, t_plane *plane,
		t_vec light_dir, double light_length)
{
	while (plane)
	{
		if (shadow_intersect_plane(ray, plane, light_dir, light_length))
			return (1);
		plane = plane->next;
	}
	return (0);
}

int	cylinder_on_the_path(t_ray *ray, t_cylinder *cylinder,
		t_vec light_dir, double light_length)
{
	while (cylinder)
	{
		if (shadow_intersect_cylinder(ray, cylinder, light_dir, light_length))
			return (1);
		cylinder = cylinder->next;
	}
	return (0);
}

int	shadow_intersect_bvh(t_ray *ray, t_bvh *box,
	t_vec light_dir)
{
	double	t[2];
	double	t_values[2];

	t_values[0] = -INFINITY;
	t_values[1] = INFINITY;
	if (light_dir.x != 0.0f)
	{
		t[0] = (box->bottom[0].x - ray->hit.x) / light_dir.x;
		t[1] = (box->top[3].x - ray->hit.x) / light_dir.x;
		t_values[0] = fmax(t_values[0], fmin(t[0], t[1]));
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (light_dir.y != 0.0f)
	{
		t[0] = (box->bottom[0].y - ray->hit.y) / light_dir.y;
		t[1] = (box->top[3].y - ray->hit.y) / light_dir.y;
		t_values[0] = fmax(t_values[0], fmin(t[0], t[1]));
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (light_dir.z != 0.0f)
	{
		t[0] = (box->bottom[0].z - ray->hit.z) / light_dir.z;
		t[1] = (box->top[3].z - ray->hit.z) / light_dir.z;
		t_values[0] = fmax(t_values[0], fmin(t[0], t[1]));
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (t_values[1] >= t_values[0] && t_values[1] > 1e-6)
			return (1);
	return (0);
}
