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
