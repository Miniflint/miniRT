#include "miniRT.h"
#include "tri_lib.h"

// cam->dir_x = x  cam->dir_y = z cam->dir = y

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

unsigned int	traceray(t_ray *ray, t_all *all)
{
	init_ray(ray);
	closest_plane(ray, all->planes);
	closest_sphere(ray, all->spheres);
	closest_cylinder(ray, all->cylinders);
	closest_box(ray, all->boxes);
	// if (bvh_on_path(ray, &all->boxes->box))
	// {
	// 	ray->color_ray.r = 1;
	// 	ray->color_ray.g = 0;
	// 	ray->color_ray.b = 0;
	// 	return(rgb_f_to_unsigned(ray->color_ray));
	// }
	if (isinf(ray->shape.t1))
		return (TRI_OPAQUE_UNSIGNED | ray->color.r << 16
			| ray->color.g << 8 | ray->color.b);
	ray->hit = scalar_multiplication_no_v(&ray->dir, ray->shape.t1);
	add_vectors(&ray->hit, &ray->start, &ray->hit);
	set_shapes(ray);
	if (dot_product(&ray->shape.normal, &ray->dir) > 0)
		ray->shape.normal = (t_vec){-ray->shape.normal.x,
			-ray->shape.normal.y, -ray->shape.normal.z};
	diffuse_light(ray, all, all->lights);
	ray->color_ray.r = ray->color_shape.r * ray->color_diffuse.r;
	ray->color_ray.g = ray->color_shape.g * ray->color_diffuse.g;
	ray->color_ray.b = ray->color_shape.b * ray->color_diffuse.b;
	return (rgb_f_to_unsigned(ray->color_ray));
}

void	start_rays(t_all *all)
{
	int				index[2];
	int				real[2];
	const int		mi_pix = all->canvas.pixel_values >> 1;
	const t_render	*render = &tri_lib()->_windows->_base_render._render;

	index[0] = mi_pix;
	real[0] = 0;
	while (real[0] < all->win_height)
	{
		real[1] = 0;
		index[1] = mi_pix;
		index[0] -= (index[0] >= all->win_height);
		while (real[1] < all->win_width)
		{
			index[1] -= (index[1] >= all->win_width);
			_replace_s_px_on_render((t_render *)render,
				traceray(&all->canvas.rays[index[0]][index[1]], all),
				(t_point2d){real[1], real[0]}, all->canvas.pixel_values);
			real[1] += all->canvas.pixel_values;
			index[1] = real[1] + mi_pix;
		}
		real[0] += all->canvas.pixel_values;
		index[0] = real[0] + mi_pix;
	}
}
