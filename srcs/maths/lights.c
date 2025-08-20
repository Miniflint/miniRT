#include "miniRT.h"
#include "tri_lib.h"

// void	add_color_ray(t_rgb *raycolor, t_rgb *lightcolor, double intensity)
// {
// 	int		color;
// 	color = (int)(((double)lightcolor->r * intensity) + raycolor->r);
// 	if (color > 255)
// 		color = 255;
// 	raycolor->r = color;
// 	color = (int)(((double)lightcolor->g * intensity) + raycolor->g);
// 	if (color > 255)
// 		color = 255;
// 	raycolor->g = color;
// 	color = (int)(((double)lightcolor->b * intensity) + raycolor->b);
// 	if (color > 255)
// 		color = 255;
// 	raycolor->b = color;
// }

void	oldIntersectRaySphere(double a, t_vec *D, t_vec *O, t_sphere *sphere, double *t1, double *t2)
{
	t_vec	CO;
	double	b;
	double	c;

	sub_vectors(O, &sphere->coord, &CO);
	b = 2 * dot_product(&CO, D);
	c = dot_product(&CO, &CO) - sphere->radius_squared;
	
	double disciminant = b * b - 4 * a * c;
	if (disciminant < 0)
	{
		*t1 = INFINITY;
		*t2 = INFINITY;
		return ;
	}
	a *= 2;
	disciminant = sqrt(disciminant); 
	*t1 = (-b + disciminant) / a;
	*t2 = (-b - disciminant) / a;
}

double	sphere_on_the_path(t_sphere *sphere, t_coord point, t_vec ray_dir, t_sphere *actual_sphere, double ray_length)
{
	double		t1, t2;
	const double a = dot_product(&ray_dir, &ray_dir);

	while (sphere)
	{
		if (sphere == actual_sphere)
		{
			sphere = sphere->next;
			continue ;
		}
		oldIntersectRaySphere(a, &ray_dir, &point, sphere, &t1, &t2);
		if ((!isinf(t1) || !isinf(t2)) && (t2 <= ray_length && t1 <= ray_length) && (t2 > 0 && t1 > 0))
		    return ((t1 - t2) / sphere->diameter);
		sphere = sphere->next;
	}
	return (0);
}

void	get_rgb_norm_light_intensity(t_rgb_f	*color, t_light *light, t_vec normal, t_coord p, t_sphere *sphere)
{
	t_vec		L;
	t_all		*all;
	double		light_length;
	double		light_length_square;
	double		intensity;
	double		diff;

	sub_vectors(&light->coord, &p, &L);
	light_length_square = L.x * L.x + L.y * L.y + L.z * L.z;
	light_length = sqrt(light_length_square);
	norm_vectors(&L, light_length, &L);
	intensity = dot_product(&normal, &L);
	if (intensity > 0)
	{
		all = __get_all();
		if (all->shadow_on)
		{
			diff = sphere_on_the_path(all->spheres, p, L, sphere, light_length);
			if (diff)
			{
				diff = (1.0 - diff);
				diff = (diff * diff);
				if (diff > 1.0)
					diff = 1.0;
				intensity *= diff;
			}
		}
		intensity *= (light->ratio * (all->distance_light / (light_length_square + all->distance_light)));
		color->r += light->rgb_norm.r * intensity;
		color->g += light->rgb_norm.g * intensity;
		color->b += light->rgb_norm.b * intensity;
	}
}

void	diffuse_light(t_ray *ray, t_all *all, t_light *light)
{
	t_rgb_f	ambiant_light;

	while (light)
	{
		get_rgb_norm_light_intensity(&ray->color_diffuse, light, ray->shape.normal, ray->hit, all->spheres);
		light = light->next;
	}
	// if (!ray->color_diffuse.r && !ray->color_diffuse.g && !ray->color_diffuse.b)
	// 	return ;
	ambiant_light = all->ambient_light.rgb_norm;
	ray->color_diffuse.r += ambiant_light.r;
	ray->color_diffuse.g += ambiant_light.g;
	ray->color_diffuse.b += ambiant_light.b;
}

// void	send_light_sphere(t_light *light, t_rgb *raycolor, t_coord p, t_sphere *sphere)
// {
// 	t_vec		normal;
// 	t_rgb_f	ambiant_light;
// 	t_rgb_f	color;

// 	color.r = 0;
// 	color.g = 0;
// 	color.b = 0;
// 	sub_vectors(&p, &sphere->coord, &normal);
// 	norm_vectors(&normal, vec_magnitude(&normal), &normal);
// 	while (light)
// 	{
// 		get_rgb_norm_light_intensity(&color, light, normal, p, sphere);
// 		light = light->next;
// 	}
// 	if (!color.r && !color.g && !color.b)
// 		return ;
// 	ambiant_light = __get_all()->ambient_light.rgb_norm;
// 	color.r += ambiant_light.r;
// 	if (color.r > 1)
// 		color.r = 1;
// 	color.g += ambiant_light.g;
// 	if (color.g > 1)
// 		color.g = 1;
// 	color.b += ambiant_light.b;
// 	if (color.b > 1)
// 		color.b = 1;
// 	raycolor->r = (double)(sphere->rgb_save.r) * color.r + 0.5;
// 	raycolor->g = (double)(sphere->rgb_save.g) * color.g + 0.5;
// 	raycolor->b = (double)(sphere->rgb_save.b) * color.b + 0.5;
// }