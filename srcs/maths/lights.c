#include "miniRT.h"
#include "tri_lib.h"

int	shadow_intersect_sphere(t_ray *ray, t_sphere *sphere, t_vec light_dir, double light_lenght)
{
	double			disciminant;
	const t_vec		CO = sub_vectors_no_v(&ray->hit, &sphere->coord);
	const double	b = 2 * dot_product((t_vec *)&CO, &light_dir);
	const double	c = dot_product((t_vec *)&CO, (t_vec *)&CO) - sphere->radius_squared;
	double			t;

	disciminant = b * b - 4.0 * c; // le a dans "b * b - 4 * a * c" supprimé car a = dot d'un vecteur unitaire avec lui même ce qui donne toujours 1
	if (disciminant < 0)
		return (0);
	disciminant = sqrt(disciminant);
	t = (-b - disciminant) / 2.0;
	if ((t >= 1e-6 && t < light_lenght))
		return (1);
	//t = (-b + disciminant) / 2.0;
	//if ((t >= 1e-6 && t < light_lenght))
	//	return (1);
	return (0);
}

int	shadow_intersect_plane(t_ray *ray, t_plane *plane, t_vec light_dir, double light_lenght)
{
    double  dot;
    double  t;
    t_vec   new_vec;

    dot = dot_product(&plane->vec, &light_dir);
    if (dot == 0)
        return (0);
    sub_vectors(&ray->hit, &plane->coord, &new_vec);
    t = -dot_product(&plane->vec, &new_vec) / dot;
	if (t >= 1e-6 && t < light_lenght)
		return (1);
	return (0);
}

int	sphere_on_the_path(t_ray *ray, t_sphere *sphere, t_vec light_dir, double light_length)
{
	while (sphere)
	{
		if ((void *)sphere == ray->shape.shape)
		{
			sphere = sphere->next;
			continue ; 
		}
		if (shadow_intersect_sphere(ray, sphere, light_dir, light_length))
			return (1);
		sphere = sphere->next;
	}
	return (0);
}

int	plane_on_the_path(t_ray *ray, t_plane *plane, t_vec light_dir, double light_length)
{
	while (plane)
	{
		if ((void *)plane == ray->shape.shape)
		{
			plane = plane->next;
			continue ; 
		}
		if (shadow_intersect_plane(ray, plane, light_dir, light_length))
			return (1);
		plane = plane->next;
	}
	return (0);
}


void	get_rgb_norm_light_intensity(t_ray *ray, t_all *all, t_light *light)
{
	t_vec		light_dir;
	double		light_length;
	double		light_length_square;
	double		intensity;

	sub_vectors(&light->coord, &ray->hit, &light_dir);
	light_length_square = light_dir.x * light_dir.x + light_dir.y * light_dir.y + light_dir.z * light_dir.z;
	light_length = sqrt(light_length_square);
	norm_vectors(&light_dir, light_length, &light_dir);
	intensity = dot_product(&ray->shape.normal, &light_dir);
	if (intensity > 0)
	{
		if (all->shadow_on && (plane_on_the_path(ray, all->planes, light_dir, light_length) || sphere_on_the_path(ray, all->spheres, light_dir, light_length)))
			return ;
		intensity *= (light->ratio * (all->distance_light / (light_length_square + all->distance_light)));
		//printf("%f\n", intensity);
		ray->color_diffuse.r += light->rgb_norm.r * intensity;
		ray->color_diffuse.g += light->rgb_norm.g * intensity;
		ray->color_diffuse.b += light->rgb_norm.b * intensity;
	}
}

void	diffuse_light(t_ray *ray, t_all *all, t_light *light)
{
	t_rgb_f	ambiant_light;

	while (light)
	{
		get_rgb_norm_light_intensity(ray, all, light);
		light = light->next;
	}
	// if (!ray->color_diffuse.r && !ray->color_diffuse.g && !ray->color_diffuse.b)
	// 	return ;
	ambiant_light = all->ambient_light.rgb_norm;
	ray->color_diffuse.r += ambiant_light.r;
	ray->color_diffuse.g += ambiant_light.g;
	ray->color_diffuse.b += ambiant_light.b;
}
