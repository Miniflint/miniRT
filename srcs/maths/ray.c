#include "miniRT.h"
#include "tri_lib.h"

// cam->dir_x = x  cam->dir_y = z cam->dir = y
void	make_perpendicular(t_cam *cam)
{
	t_vec	ideal_up;
	double	mag;

	ideal_up = (t_vec){.x = 0, .y = 0, .z = 1};
	if (fabs(dot_product(&cam->dir, &ideal_up)) > 0.9999f)
		ideal_up = (t_vec){.x = 0, .y = 1, .z = 0};
	cross_product(&cam->dir, &ideal_up, &cam->dir_x);
	mag = dot_product(&cam->dir_x, &cam->dir_x);
	norm_vectors(&cam->dir_x, mag, &cam->dir_x);
	cross_product(&cam->dir, &cam->dir_x, &cam->dir_y);
	mag = dot_product(&cam->dir_y, &cam->dir_y);
	norm_vectors(&cam->dir_y, mag, &cam->dir_y);
}

void	init_ray(t_ray *ray)
{
	ray->color_ray = (t_rgb_f){0, 0, 0};
	ray->color_shape = (t_rgb_f){0, 0, 0};
	ray->color_diffuse = (t_rgb_f){0, 0, 0};
	ray->shape.type = CAMERA;
	ray->shape.shape = NULL;
	ray->shape.t1 = INFINITY;
	ray->shape.t2 = INFINITY;
}

static void	set_ts(double t, t_ray *ray, t_sphere *sphere)
{
	if (t >= 1e-6 && (isinf(ray->shape.t1) || t < ray->shape.t1))
	{
		ray->shape.t1 = t;
		ray->shape.shape = sphere;
		ray->shape.type = SPHERE;
		return ;
	}
}

void	intersect_ray_sphere(t_ray *ray, t_sphere *sphere)
{
	double			disciminant;
	double			t;
	const t_vec		co = sub_vectors_no_v(&ray->start, &sphere->coord);
	const double	b = 2 * dot_product((t_vec *)&co, &ray->dir);
	const double	c
		= dot_product((t_vec *)&co, (t_vec *)&co) - sphere->radius_squared;

	disciminant = b * b - 4.0 * c;
	if (disciminant < 0)
		return ;
	disciminant = sqrt(disciminant);
	t = (-b - disciminant) / 2;
	set_ts(t, ray, sphere);
	t = (-b + disciminant) / 2;
	set_ts(t, ray, sphere);
}

void	closest_sphere(t_ray *ray, t_sphere *sphere)
{
	while (sphere)
	{
		intersect_ray_sphere(ray, sphere);
		sphere = sphere->next;
	}
}

void	closest_plane(t_ray *ray, t_plane *plane)
{
	while (plane)
	{
		intersect_plane(ray, plane);
		plane = plane->next;
	}
}

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
	{
		set_cylinder(ray, (t_cylinder *)ray->shape.shape);
	}
}

//closest_cylinder(ray, all->cylinders);
unsigned int	traceray(t_ray *ray, t_all *all)
{
	init_ray(ray);
	closest_plane(ray, all->planes);
	closest_sphere(ray, all->spheres);
	closest_cylinder(ray, all->cylinders);
	if (isinf(ray->shape.t1))
		return (TRI_OPAQUE_UNSIGNED | ray->color.r << 16
			| ray->color.g << 8 | ray->color.b);
	ray->hit = scalar_multiplication_no_v(&ray->dir, ray->shape.t1);
	add_vectors(&ray->hit, &ray->start, &ray->hit);
	set_shapes(ray);
	diffuse_light(ray, all, all->lights);
	ray->color_ray.r = ray->color_shape.r * ray->color_diffuse.r;
	ray->color_ray.g = ray->color_shape.g * ray->color_diffuse.g;
	ray->color_ray.b = ray->color_shape.b * ray->color_diffuse.b;
	return (rgb_f_to_unsigned(ray->color_ray));
}

void	start_rays(t_all *all)
{
	int			index[2];
	int			real[2];
	const int	mi_pix = all->canvas.pixel_values >> 1;

	index[0] = mi_pix;
	real[0] = 0;
	while (real[0] < all->win_height)
	{
		real[1] = 0;
		index[1] = mi_pix;
		if (index[0] >= all->win_height)
			index[0] = all->win_height - 1;
		while (real[1] < all->win_width)
		{
			if (index[1] >= all->win_width)
				index[1] = all->win_width - 1;
			_replace_s_px_on_render(&tri_lib()->_windows->_base_render._render,
				traceray(&all->canvas.rays[index[0]][index[1]], all),
				(t_point2d){real[1], real[0]}, all->canvas.pixel_values);
			real[1] += all->canvas.pixel_values;
			index[1] = real[1] + mi_pix;
		}
		real[0] += all->canvas.pixel_values;
		index[0] = real[0] + mi_pix;
	}
}
