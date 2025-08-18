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

void	IntersectRaySphere(double a, t_vec *D, t_vec *O, t_sphere *sphere, double *t1, double *t2)
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


unsigned int	spheres(t_ray *ray, t_all *all, t_shape_closest *shape)
{
	t_sphere	*sphere;
	t_coord		hit_point;
	double		closest_t;
	const double a = dot_product(&ray->dir, &ray->dir);

	closest_t = INFINITY;
	sphere = all->spheres;
	while (sphere)
	{
		IntersectRaySphere(a, &ray->dir, &ray->start, sphere, &shape->sp_t1, &shape->sp_t2);
		if (!isinf(shape->sp_t1) && shape->sp_t1 < closest_t && shape->sp_t1 > 1)
		{
			closest_t = shape->sp_t1;
			shape->sp_closest = sphere;
		}
		if (!isinf(shape->sp_t2) && shape->sp_t2 < closest_t && shape->sp_t2 > 1)
		{
			closest_t = shape->sp_t2;
			shape->sp_closest = sphere;
		}
		sphere = sphere->next;
	}
	if (sphere && !isinf(closest_t))
	{
		shape->colors = shape->sp_closest->rgb;
		shape->shape = (void *)shape->sp_closest;
		hit_point = scalar_multiplication_no_v(&ray->dir, closest_t);
		add_vectors(&hit_point, &all->camera.viewpoint, &hit_point);
		send_light_sphere(all->lights, &shape->colors, ray->start, shape->sp_closest);
	}
	return (TRI_OPAQUE_UNSIGNED | shape->colors.r << 16 | shape->colors.g << 8 | shape->colors.b);

}

unsigned int	planes(t_ray *ray, t_all *all, t_shape_closest *shape)
{
	t_plane	*plane;
	double	closest_t;
	t_vec	hit_point;

	plane = all->planes;
	while (plane)
	{
		intersect_plane(plane, ray, &shape->pl_t1);
		if (!isinf(shape->pl_t1) && shape->pl_t1 < closest_t && shape->pl_t1 > 1)
		{
			closest_t = shape->pl_t1;
			shape->pl_closest = plane;
		}
		plane = plane->next;
	}
	if (plane && !isinf(closest_t))
	{
		ray->color = shape->pl_closest->rgb;
		hit_point = scalar_multiplication_no_v(&ray->dir, closest_t);
		add_vectors(&hit_point, &all->camera.viewpoint, &hit_point);
	}
	return (TRI_OPAQUE_UNSIGNED | ray->color.r << 16 | ray->color.g << 8 | ray->color.b);
}

void	t_shape_zero(t_shape_closest *s)
{
	s->t = INFINITY;
	s->normal = (t_vec){0, 0, 0};
	s->shape = NULL;
	s->cy_closest = NULL;
	s->ob_closest = NULL;
	s->sp_closest = NULL;
	s->pl_closest = NULL;
	s->pl_t1 = INFINITY;
	s->sp_t1 = INFINITY;
	s->sp_t2 = INFINITY;
}

int	get_closest(t_shape_closest closest)
{
	if (closest.sp_t1 < closest.pl_t1)
		return (1);
	return (2);
}

unsigned int	traceray(t_ray *ray, t_all *all)
{
	t_shape_closest	closest;
	unsigned	int	sp_color[4];

	t_shape_zero(&closest);
	sp_color[0] = spheres(ray, all, &closest);
	sp_color[1] = planes(ray, all, &closest);
	return (sp_color[0]);
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
	//while (j_start < tmp)
	//{
	////column motif
	//i_start = 0;
	//while (i_start < tmp)
	//{
	////motif square space
	//i = i_start;
	//pix_y_base = -((all->win_height >> 1) * unit);
	//pix_x_base = -((all->win_width >> 1) * unit);
	//pix_y = pix_y_base + i * unit;
	//while (i < all->win_height)
	//{
	//	j = j_start;
	//	scalar_multiplication(&all->camera.dir_y, pix_y, &dir_y);
	//	pix_x = pix_x_base + j * unit;
	//	while (j < all->win_width)
	//	{
	//		scalar_multiplication(&all->camera.dir_x, pix_x, &dir_x);
	//		add_vectors(&all->camera.dir, &dir_x, &ray);
	//		add_vectors(&ray, &dir_y, &ray);
	//		color = traceray(&ray, all);
	//		lib->replace_pixel_on_window(lib->_windows, color, j, i);
	//		j += tmp;
	//		pix_x += unit * tmp;
	//	}
	//	pix_y += unit * tmp;
	//	i += tmp;
	//}
	////end motif square space
	//i_start++;
	//}
	////end column motif
	//lib->draw_windows();
	//j_start++;
	//}
	////end line motif
//
//}
