/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 02:46:42 by hermesrolle       #+#    #+#             */
/*   Updated: 2025/09/07 02:46:44 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "tri_lib.h"

// int	shadow_intersect_sphere(t_ray *ray, t_sphere *sphere,
// 			t_vec light_dir, double light_lenght)
// {
// 	double			disciminant;
// 	const t_vec		CO = sub_vectors_no_v(&ray->hit, &sphere->coord);
// 	const double	b = 2 * dot_product((t_vec *)&CO, &light_dir);
// 	const double	c = dot_product((t_vec *)&CO, (t_vec *)&CO)
// - sphere->radius_squared;
// 	double			t;

// 	disciminant = b * b - 4.0 * c;
// le a dans "b * b - 4 * a * c" supprimé car
// a = dot d'un vecteur unitaire avec lui même ce qui donne toujours 1
// 	if (disciminant < 0)
// 		return (0);
// 	disciminant = sqrt(disciminant);
// 	t = (-b - disciminant) / 2.0;
// 	if ((t >= 1e-6 && t < light_lenght))
// 		return (1);
// 	//t = (-b + disciminant) / 2.0;
// 	//if ((t >= 1e-6 && t < light_lenght))
// 	//	return (1);
// 	return (0);
// }

int	check_t(t_quad q, t_ray *ray, t_cylinder *cylinder, t_light_vec l)
{
	t_vec		p;
	double		mag;
	const t_vec	*cyl_co = &cylinder->coord;

	q.t = (q.b - q.discriminant) / q.a;
	if (q.t >= 1e-6 && q.t < l.light_lenght)
	{
		add_vectors(&ray->hit,
			scalar_multiplication(&l.light_dir, q.t, &p), &p);
		mag = dot_product(sub_vectors(&p, (t_vec *)cyl_co, &p), &cylinder->vec);
		if (mag >= 0
			&& mag <= cylinder->height && !isnan(mag) && !isinf(mag))
			return (1);
	}
	q.t = (q.b + q.discriminant) / q.a;
	if (q.t >= 1e-6 && q.t < l.light_lenght)
	{
		add_vectors(&ray->hit,
			scalar_multiplication(&l.light_dir, q.t, &p), &p);
		mag = dot_product(sub_vectors(&p, (t_vec *)cyl_co, &p), &cylinder->vec);
		if (mag >= 0
			&& mag <= cylinder->height && !isnan(mag) && !isinf(mag))
			return (1);
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
	light_length_square = light_dir.x * light_dir.x
		+ light_dir.y * light_dir.y + light_dir.z * light_dir.z;
	light_length = sqrt(light_length_square);
	norm_vectors(&light_dir, light_length, &light_dir);
	intensity = dot_product(&ray->shape.normal, &light_dir);
	if (intensity > 0)
	{
		if (all->shadow_on
			&& (plane_on_the_path(ray, all->planes, light_dir, light_length)
				|| sphere_on_the_path(ray, all->spheres, light_dir,
					light_length) || cylinder_on_the_path(ray, all->cylinders,
					light_dir, light_length)))
			return ;
		intensity *= (light->ratio * (all->distance_light
					/ (light_length_square + all->distance_light)));
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
	ambiant_light = all->ambient_light.rgb_norm;
	ray->color_diffuse.r += ambiant_light.r;
	ray->color_diffuse.g += ambiant_light.g;
	ray->color_diffuse.b += ambiant_light.b;
}
