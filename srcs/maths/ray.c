#include "miniRT.h"
#include "tri_lib.h"

// cam->dir_x = x  cam->dir_y = z cam->dir = y
void make_perpendicular(t_cam *cam)
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

// void	IntersectRaySphere(double a, t_vec *D, t_vec *O, t_sphere *sphere, double *t1, double *t2)
// {
// 	t_vec	CO;
// 	double	b;
// 	double	c;

// 	sub_vectors(O, &sphere->coord, &CO);
// 	b = 2 * dot_product(&CO, D);
// 	c = dot_product(&CO, &CO) - sphere->radius_squared;
	
// 	double disciminant = b * b - 4 * a * c;
// 	if (disciminant < 0)
// 	{
// 		*t1 = INFINITY;
// 		*t2 = INFINITY;
// 		return ;
// 	}
// 	a *= 2;
// 	disciminant = sqrt(disciminant); 
// 	*t1 = (-b + disciminant) / a;
// 	*t2 = (-b - disciminant) / a;
// }

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

void	IntersectRaySphere(t_ray *ray, t_sphere *sphere)
{
	t_vec	CO;
	double	b;
	double	c;
	double	t1;
	double	t2;

	sub_vectors(&ray->start, &sphere->coord, &CO);
	b = 2 * dot_product(&CO, &ray->dir);
	c = dot_product(&CO, &CO) - sphere->radius_squared;
	
	double disciminant = b * b - 4.0 * c; // le a dans "b * b - 4 * a * c" supprimé car a = dot d'un vecteur unitaire avec lui même ce qui donne toujours 1
	if (disciminant < 0)
		return ;
	disciminant = sqrt(disciminant); 
	t1 = (-b - disciminant) / 2.0;
	t2 = (-b + disciminant) / 2.0; //2 à la place de a * 2 car a = 1
	if (t1 >= 1e-6 && (isinf(ray->shape.t1) || t1 < ray->shape.t1))
	{
		ray->shape.t1 = t1;
		if (t2 >= 1e-6)
			ray->shape.t2 = t2;
		else
			ray->shape.t2 = INFINITY;
	}
	else if (t2 >= 1e-6 && (isinf(ray->shape.t1) || t2 < ray->shape.t1))
	{
		ray->shape.t1 = t2;
		ray->shape.t2 = INFINITY;
	}
	else
		return ;
	ray->shape.shape = sphere;
	ray->shape.type = SPHERE;
}

void	closest_sphere(t_ray *ray, t_sphere *sphere)
{
	while (sphere)
	{
		IntersectRaySphere(ray, sphere);
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

unsigned int	traceray(t_ray *ray, t_all *all)
{
	init_ray(ray);
	closest_plane(ray, all->planes);
	//closest_cylinder(ray, all->cylinders);
	closest_sphere(ray, all->spheres);
	if (isinf(ray->shape.t1))
		return (TRI_OPAQUE_UNSIGNED | ray->color.r << 16 | ray->color.g << 8 | ray->color.b);
	ray->hit = scalar_multiplication_no_v(&ray->dir, ray->shape.t1);
	add_vectors(&ray->hit, &ray->start, &ray->hit);
	if (ray->shape.type == SPHERE)
	{
		ray->shape.origin = ((t_sphere *)(ray->shape.shape))->coord;
		sub_vectors(&ray->hit, &ray->shape.origin, &ray->shape.normal);
		norm_vectors(&ray->shape.normal, vec_magnitude(&ray->shape.normal), &ray->shape.normal);
		ray->color_shape = ((t_sphere *)(ray->shape.shape))->color;
	}
	else if (ray->shape.type == PLANE)
	{
		ray->shape.origin = ((t_plane *)(ray->shape.shape))->coord;
		ray->shape.normal = ((t_plane *)(ray->shape.shape))->vec;
		ray->color_shape = ((t_plane *)(ray->shape.shape))->color;
	}
	diffuse_light(ray, all, all->lights);
	//ray->color_diffuse = clamp_rgb_f(ray->color_diffuse);
	ray->color_ray.r = ray->color_shape.r * ray->color_diffuse.r;
	ray->color_ray.g = ray->color_shape.g * ray->color_diffuse.g;
	ray->color_ray.b = ray->color_shape.b * ray->color_diffuse.b;
	return (rgb_f_to_unsigned(ray->color_ray));
}

void start_rays(t_all *all)
{
	int i;
	int j;
	int	real_i;
	int	real_j;
	int	mi_pix;
	t_tri_lib *lib;

	lib = tri_lib();
	mi_pix = all->canvas.pixel_values / 2;
	i = mi_pix;
	real_i = 0;
	while (real_i < all->win_height)
	{
		real_j = 0;
		j = mi_pix;
		if (i >= all->win_height)
			i = all->win_height - 1;
		while (real_j < all->win_width)
		{
			if (j >= all->win_width)
				j = all->win_width - 1;
			_replace_sized_pixel_on_render(&lib->_windows->_base_render._render, traceray(&all->canvas.rays[i][j], all), real_j, real_i, all->canvas.pixel_values);
			// _replace_pixel_on_render(&lib->_windows->_base_render._render, traceray(&all->canvas.rays[i][j], all), real_j, real_i);
			real_j += all->canvas.pixel_values;
			j = real_j + mi_pix;
		}
		real_i += all->canvas.pixel_values;
		i = real_i + mi_pix;
	}
	// lib->draw_windows();
}
