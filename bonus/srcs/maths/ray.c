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
	// ray->color_ray = (t_rgb_f){0, 0, 0};
	// ray->color_shape = (t_rgb_f){0, 0, 0};
	ray->color_diffuse = (t_rgb_f){0, 0, 0};
	ray->shape.type = CAMERA;
	ray->shape.shape = NULL;
	ray->shape.t1 = INFINITY;
	ray->shape.t2 = INFINITY;
}

/*
		tri_lib()->put_pixel_to_render(render, (t_argb){
			.a=0.5, .r=(255 % (bvh->depth + 1)), .g=(255 % (bvh->depth + 1)), .b= (255 % (bvh->depth + 1))}, ray->y, ray->x);
*/

void	traverse_bvh(t_ray *ray, t_hitbox *bvh, t_render *render, int hb)
{
	if (!bvh)
		return ;
	if (intersect_hitbox(ray, &bvh->box))
	{
		if (hb)
		{
			tri_lib()->put_pixel_to_render(render, (t_argb){
				.a=0.125,
				.r=255,
				.g=255,
				.b=255}, ray->y, ray->x);
		}
		if (bvh->node_type == LEAF)
		{
			if (bvh->type == SPHERE)
				intersect_ray_sphere(ray, (t_sphere *)bvh->shape);
			else if (bvh->type == CYLINDER)
				intersect_cylinder(ray, (t_cylinder *)bvh->shape);
			else if (bvh->type == BOX)
				intersect_box(ray, (t_box *)bvh->shape);
			return ;
		}
		if (bvh->left)
			traverse_bvh(ray, bvh->left, render, hb);
		if (bvh->right)
			traverse_bvh(ray, bvh->right, render, hb);
	}
}

void	traceray(t_ray *ray, t_all *all)
{
	init_ray(ray);
	traverse_bvh(ray, all->bvh, all->render_hb, all->render_hitbox);
	closest_plane(ray, all->planes);
	if (isinf(ray->shape.t1))
	{
		ray->color_ray = ray->color;
		return ;
	}
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
}

// unsigned int	traceray(t_ray *ray, t_all *all)
// {
// 	init_ray(ray);
// 	closest_plane(ray, all->planes);
// 	closest_sphere(ray, all->spheres);
// 	closest_cylinder(ray, all->cylinders);
// 	closest_box(ray, all->boxes);
// 	// if (bvh_on_path(ray, &all->boxes->box))
// 	// {
// 	// 	ray->color_ray.r = 1;
// 	// 	ray->color_ray.g = 0;
// 	// 	ray->color_ray.b = 0;
// 	// 	return(rgb_f_to_unsigned(ray->color_ray));
// 	// }
// 	if (isinf(ray->shape.t1))
// 		return (TRI_OPAQUE_UNSIGNED | ray->color.r << 16
// 			| ray->color.g << 8 | ray->color.b);
// 	ray->hit = scalar_multiplication_no_v(&ray->dir, ray->shape.t1);
// 	add_vectors(&ray->hit, &ray->start, &ray->hit);
// 	set_shapes(ray);
// 	if (dot_product(&ray->shape.normal, &ray->dir) > 0)
// 		ray->shape.normal = (t_vec){-ray->shape.normal.x,
// 			-ray->shape.normal.y, -ray->shape.normal.z};
// 	diffuse_light(ray, all, all->lights);
// 	ray->color_ray.r = ray->color_shape.r * ray->color_diffuse.r;
// 	ray->color_ray.g = ray->color_shape.g * ray->color_diffuse.g;
// 	ray->color_ray.b = ray->color_shape.b * ray->color_diffuse.b;
// 	return (rgb_f_to_unsigned(ray->color_ray));
// }

int	start_rays_thread(t_all *all, t_threads *thread)
{
	int				index[2];
	int				real[2];
	const int		mi_pix = all->canvas.pixel_values >> 1;

	real[0] = thread->start;
	index[0] = mi_pix + real[0];
	while (real[0] < thread->end)
	{
		real[1] = 0;
		index[1] = mi_pix;
		index[0] -= (index[0] >= thread->end);
		while (real[1] < all->win_width)
		{
			index[1] -= (index[1] >= all->win_width);
			all->canvas.rays[index[0]][index[1]].y = index[0];
			all->canvas.rays[index[0]][index[1]].x = index[1];
			if (all->render_hitbox)
				_replace_s_px_on_render(all->render_hb, 0,
					(t_point2d){real[1], real[0]}, all->canvas.pixel_values);
			traceray(&all->canvas.rays[index[0]][index[1]], all);
			real[1] += all->canvas.pixel_values;
			index[1] = real[1] + mi_pix;
		}
		if (get_thread_mode_pause(all, thread) == (t_thread_mode)STOP)
			return (1);
		else if (thread->mode == (t_thread_mode)RESET)
			return (0);
		real[0] += all->canvas.pixel_values;
		index[0] = real[0] + mi_pix;
	}
	return (0);
}

void	start_rays(t_all *all)
{
	int				index[2];
	int				real[2];
	const int		mi_pix = all->canvas.pixel_values >> 1;

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
			all->canvas.rays[index[0]][index[1]].y = index[1];
			all->canvas.rays[index[0]][index[1]].x = index[0];
			_replace_s_px_on_render(all->render_hb, 0,
				(t_point2d){real[1], real[0]}, all->canvas.pixel_values);
			traceray(&all->canvas.rays[index[0]][index[1]], all);
			real[1] += all->canvas.pixel_values;
			index[1] = real[1] + mi_pix;
		}
		real[0] += all->canvas.pixel_values;
		index[0] = real[0] + mi_pix;
	}
}

// void	start_rays(t_all *all)
// {
// 	int				index[2];
// 	int				real[2];
// 	const int		mi_pix = all->canvas.pixel_values >> 1;
// 	const t_render	*render = &tri_lib()->_windows->_base_render._render;

// 	index[0] = mi_pix;
// 	real[0] = 0;
// 	while (real[0] < all->win_height)
// 	{
// 		real[1] = 0;
// 		index[1] = mi_pix;
// 		index[0] -= (index[0] >= all->win_height);
// 		while (real[1] < all->win_width)
// 		{
// 			index[1] -= (index[1] >= all->win_width);
// 			_replace_s_px_on_render((t_render *)render,
// 				traceray(&all->canvas.rays[index[0]][index[1]], all),
// 				(t_point2d){real[1], real[0]}, all->canvas.pixel_values);
// 			real[1] += all->canvas.pixel_values;
// 			index[1] = real[1] + mi_pix;
// 		}
// 		real[0] += all->canvas.pixel_values;
// 		index[0] = real[0] + mi_pix;
// 	}
// }
