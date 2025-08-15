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
int	sphere_on_the_path(t_sphere *sphere, t_coord point, t_vec ray_dir, t_sphere *actual_sphere, double ray_length)
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
		IntersectRaySphere(a, &ray_dir, &point, sphere, &t1, &t2);
		if ((!isinf(t1) && t1 <= ray_length) || (!isinf(t2) && t2 <= ray_length))
		    return (1);
		sphere = sphere->next;
	}
	return (0);
}

t_rgb	add_color_ray(t_rgb_norm ambientlight, t_rgb_norm lightcolor, t_rgb spherecolor, double intensity)
{
	t_rgb_norm	ch_i;

	ch_i.r = lightcolor.r * intensity + ambientlight.r;
	if (ch_i.r > 1)
		ch_i.r = 1;
	ch_i.g = lightcolor.g * intensity + ambientlight.g;
	if (ch_i.g > 1)
		ch_i.g = 1;
	ch_i.b = lightcolor.b * intensity + ambientlight.b;
	if (ch_i.b > 1)
		ch_i.b = 1;
	return ((t_rgb){0, (t_color)((double)spherecolor.r * ch_i.r), (t_color)((double)spherecolor.g * ch_i.g), (t_color)((double)spherecolor.b * ch_i.b)});
}

void	get_rgb_norm_light_intensity(t_rgb_norm	*color, t_light *light, t_vec normal, t_coord p, t_sphere *sphere)
{
	t_vec		L;
	t_all		*all;
	double		light_length;
	double		intensity;

	sub_vectors(&light->coord, &p, &L);
	light_length = vec_magnitude(&L);
	norm_vectors(&L, vec_magnitude(&L), &L);
	intensity = dot_product(&normal, &L);
	if (intensity > 0)
	{
		all = __get_all();
		if (all->shadow_on && sphere_on_the_path(all->spheres, p, L, sphere, light_length))
			return ;
		intensity *= light->ratio;
		color->r += light->rgb_norm.r * intensity;
		color->g += light->rgb_norm.g * intensity;
		color->b += light->rgb_norm.b * intensity;
	}
}

void	send_light_sphere(t_light *light, t_rgb *raycolor, t_coord p, t_sphere *sphere)
{
	t_vec		normal;
	t_rgb_norm	ambiant_light;
	t_rgb_norm	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	sub_vectors(&p, &sphere->coord, &normal);
	norm_vectors(&normal, vec_magnitude(&normal), &normal);
	while (light)
	{
		get_rgb_norm_light_intensity(&color, light, normal, p, sphere);
		light = light->next;
	}
	if (!color.r && !color.g && !color.b)
	return ;
	ambiant_light = __get_all()->ambient_light.rgb_norm;
	color.r += ambiant_light.r;
	if (color.r > 1)
		color.r = 1;
	color.g += ambiant_light.g;
	if (color.g > 1)
		color.g = 1;
	color.b += ambiant_light.b;
	if (color.b > 1)
		color.b = 1;
	raycolor->r = (double)(sphere->rgb_save.r) * color.r + 0.5;
	raycolor->g = (double)(sphere->rgb_save.g) * color.g + 0.5;
	raycolor->b = (double)(sphere->rgb_save.b) * color.b + 0.5;
}

// void	send_light_sphere(t_light *light, t_rgb *raycolor, t_coord p, t_coord c)
// {
// 	t_vec	L;
// 	t_vec	N;
// 	double	a_cos;
// 	double	intensity;
// 	double	surface_spread;

// 	sub_vectors(&light->coord, &p, &L);
// 	sub_vectors(&p, &c, &N);
// 	norm_vectors(&L, vec_magnitude(&L), &L);
// 	norm_vectors(&N, vec_magnitude(&N), &N);
// 	a_cos = 1- dot_product(&N, &L);
// 	if (a_cos <= 0)
// 		return ;
// 	surface_spread = (light->ratio / 2.0) / a_cos;
// 	intensity = surface_spread / light->ratio;
// 	add_color_ray(raycolor, &light->rgb, intensity);
// }
