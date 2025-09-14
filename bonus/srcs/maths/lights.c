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

int	shadow_traverse_bvh(t_ray *ray,
	t_hitbox *bvh,
	t_render *render,
	t_vec light_dir,
	double light_length
)
{
	if (!bvh)
		return (0);
	if (shadow_intersect_bvh(ray, &bvh->box, light_dir))
	{
		if (bvh->node_type == LEAF)
		{
			if ((bvh->type == SPHERE && shadow_intersect_sphere(ray, (t_sphere *)bvh->shape,
				light_dir, light_length))
				|| (bvh->type == BOX && shadow_intersect_bvh(ray, bvh->shape,
					light_dir)) // Manque light length
				|| (bvh->type == CYLINDER && shadow_intersect_cylinder(ray, bvh->shape,
					light_dir, light_length)))
				return (1);
		}
		if ((bvh->left && shadow_traverse_bvh(ray, bvh->left, render, light_dir, light_length))
			|| (bvh->right && shadow_traverse_bvh(ray, bvh->right, render, light_dir, light_length)))
			return (1);
	}
	return (0);
}

int	shadow_traverse_bvh_iter(t_ray *ray, t_hitbox *bvh,
	t_vec light_dir,
	double light_length)
{
	t_queue		q;
	t_hitbox	*curr;

	if (queue_init(&q, __get_all()->nb_shapes))
		return (1);
	queue_push(&q, bvh);
	while (!queue_is_empty(&q))
	{
		curr = queue_pop(&q);
		if (!curr || !shadow_intersect_bvh(ray, &curr->box, light_dir))
			continue ;
		if (curr->node_type == LEAF)
		{
			if (curr->type == SPHERE &&
				shadow_intersect_sphere(ray, curr->shape, light_dir, light_length))
				return (queue_free(&q), 1);
			else if (curr->type == BOX
				&& shadow_intersect_bvh(ray, curr->shape, light_dir))
				return (queue_free(&q), 1);
			else if (curr->type == CYLINDER
				&& shadow_intersect_cylinder(ray, curr->shape, light_dir, light_length))
				return (queue_free(&q), 1);
			else if (curr->type == TRIANGLE
				&& shadow_intersect_triangle(ray, curr->shape, light_dir, light_length))
				return (queue_free(&q), 1);
		}
		else
		{
			if (curr->left)
				queue_push(&q, curr->left);
			if (curr->right)
				queue_push(&q, curr->right);
		}
	}
	queue_free(&q);
	return (0);
}

void	specular(t_ray *ray, t_vec light_dir, t_light *light, double light_scale)
{
	t_vec	v; //= ray->dir inverser
	t_vec	h;
	double	ndoth;
	double	intensity;

	v = scalar_multiplication_no_v(&ray->dir, -1);
	add_vectors(&light_dir, &v, &h);
	norm_vectors(&h, vec_magnitude(&h), &h);
	ndoth = dot_product(&ray->shape.normal, &h);
	if (ndoth <= 0)
		return ;
	intensity = ray->shape.material.ks * pow(ndoth, ray->shape.material.shininess) * light_scale;
	ray->color_specular.r += light->rgb_norm.r * intensity;
	ray->color_specular.g += light->rgb_norm.g * intensity;
	ray->color_specular.b += light->rgb_norm.b * intensity;
}

void	get_rgb_norm_light_intensity(t_ray *ray, t_all *all, t_light *light)
{
	t_vec		light_dir;
	double		light_length;
	double		light_length_square;
	double		intensity;
	double		light_scale;

	sub_vectors(&light->coord, &ray->hit, &light_dir);
	light_length_square = light_dir.x * light_dir.x
		+ light_dir.y * light_dir.y + light_dir.z * light_dir.z;
	light_length = sqrt(light_length_square);
	norm_vectors(&light_dir, light_length, &light_dir);
	intensity = dot_product(&ray->shape.normal, &light_dir);
	if (intensity >= 0)
	{	
		if (all->shadow_on
			&&
				((plane_on_the_path(ray, all->planes,
					light_dir, light_length))
			#ifndef BVH
				|| (sphere_on_the_path(ray, all->spheres,
					light_dir, light_length))
				|| (box_on_path(ray, all->boxes,
					light_dir))
				|| (cylinder_on_the_path(ray, all->cylinders,
					light_dir, light_length))))
			# else
				|| shadow_traverse_bvh_iter(ray, all->bvh, light_dir, light_length)))
			# endif
				return ;
		light_scale = (light->ratio * (all->distance_light
					/ (light_length_square + all->distance_light)));
		specular(ray, light_dir, light, light_scale);
		intensity *= light_scale;
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
