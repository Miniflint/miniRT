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

void	init_ray(t_ray *ray, t_all *all)
{
	// ray->color_ray = (t_rgb_f){0, 0, 0};
	if (all->render_hitbox)
		_replace_s_px_on_render(all->render_hb, 0, (t_point2d){ray->y, ray->x}, all->canvas.pixel_values);
	ray->color_shape = (t_rgb_f){0, 0, 0};
	ray->color_diffuse = (t_rgb_f){0, 0, 0};
	ray->color_specular = (t_rgb_f){0, 0, 0};
	ray->shape.type = CAMERA;
	ray->shape.shape = NULL;
	ray->reflection = 1;
	ray->shape.t1 = INFINITY;
	ray->shape.t2 = INFINITY;
}

// ReflectRay(R, N) {
//     return 2 * N * dot(N, R) - R;
// }

void	init_reflect_ray(t_ray *ray, t_all *all, t_rgb_f *ray_color_save)
{
	t_vec	vec;
	t_vec	vec2;

	(void)all;
	// ray->color_ray = (t_rgb_f){0, 0, 0};
	*ray_color_save = ray->color_ray;
	ray->color_shape = (t_rgb_f){0, 0, 0};
	ray->color_diffuse = (t_rgb_f){0, 0, 0};
	ray->color_specular = (t_rgb_f){0, 0, 0};
	ray->start = ray->hit;
	vec = scalar_multiplication_no_v(&ray->shape.normal, 2);
	vec2 = scalar_multiplication_no_v(&vec, dot_product(&ray->shape.normal, &ray->dir));
	ray->dir = sub_vectors_no_v(&vec2, &ray->dir);
	ray->shape.type = CAMERA;
	ray->shape.shape = NULL;
	ray->shape.t1 = INFINITY;
	ray->shape.t2 = INFINITY;
}

/*
		tri_lib()->put_pixel_to_render(render, (t_argb){
			.a=0.5, .r=(255 % (bvh->depth + 1)), .g=(255 % (bvh->depth + 1)), .b= (255 % (bvh->depth + 1))}, ray->y, ray->x);
*/

// void	traverse_bvh(t_ray *ray, t_hitbox *bvh, t_render *render, int hb)
// {
// 	if (!bvh)
// 		return ;
// 	if (intersect_hitbox(ray, &bvh->box))
// 	{
// 		if (hb)
// 		{
// 			tri_lib()->put_pixel_to_render(render, (t_argb){
// 				.a=0.125,
// 				.r=255,
// 				.g=255,
// 				.b=255}, ray->y, ray->x);
// 		}
// 		if (bvh->node_type == LEAF)
// 		{
// 			if (bvh->type == SPHERE)
// 				intersect_ray_sphere(ray, (t_sphere *)bvh->shape);
// 			else if (bvh->type == CYLINDER)
// 				intersect_cylinder(ray, (t_cylinder *)bvh->shape);
// 			else if (bvh->type == BOX)
// 				intersect_box(ray, (t_box *)bvh->shape);
// 			return ;
// 		}
// 		if (bvh->left)
// 			traverse_bvh(ray, bvh->left, render, hb);
// 		if (bvh->right)
// 			traverse_bvh(ray, bvh->right, render, hb);
// 	}
// }

void	traverse_bvh_iter(t_ray *ray, t_hitbox *bvh, t_render *render, int hb)
{
	t_queue		q;
	t_hitbox	*curr;
	const t_all	*all = __get_all();

	if (queue_init(&q, all->nb_shapes))
		return ;
	queue_push(&q, bvh);
	while (!queue_is_empty(&q))
	{
		curr = queue_pop(&q);
		if (!curr || !intersect_hitbox(ray, &curr->box))
			continue ;
		if (hb)
			tri_lib()->put_pixel_to_render(render, (t_argb){.a=0.25, .r=255,
				.g=255,.b=255}, ray->y, ray->x);
		if (curr->node_type == LEAF)
		{
			if (curr->type == SPHERE && all->render_on)
				intersect_ray_sphere(ray, (t_sphere *)curr->shape);
			else if (curr->type == CYLINDER)
				intersect_cylinder(ray, (t_cylinder *)curr->shape);
			else if (curr->type == BOX)
				intersect_box(ray, (t_box *)curr->shape);
			else if (curr->type == TRIANGLE)
				intersect_triangle(ray, (t_face *)curr->shape);
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
}

void	get_diffuse_light(t_ray *ray, t_all *all)
{
	if (isinf(ray->shape.t1))
	{
		ray->color_ray = ray->color;
		ray->to_draw = 1;
		return ;
	}
	ray->hit = scalar_multiplication_no_v(&ray->dir, ray->shape.t1);
	add_vectors(&ray->hit, &ray->start, &ray->hit);
	set_shapes(ray);
	if (dot_product(&ray->shape.normal, &ray->dir) > 0)
		ray->shape.normal = (t_vec){-ray->shape.normal.x,
			-ray->shape.normal.y, -ray->shape.normal.z};
	diffuse_light(ray, all, all->lights);
	ray->color_ray.r = ray->color_shape.r * ray->color_diffuse.r + ray->color_specular.r;
	ray->color_ray.g = ray->color_shape.g * ray->color_diffuse.g + ray->color_specular.g;
	ray->color_ray.b = ray->color_shape.b * ray->color_diffuse.b + ray->color_specular.b;
	ray->to_draw = 1;
}

void	get_closest_color(t_ray *ray, t_all *all)
{
	init_ray(ray, all);
	closest_plane(ray, all->planes);
	#ifndef BVH
		closest_sphere(ray, all->spheres);
		closest_cylinder(ray, all->cylinders);
		closest_box(ray, all->boxes);
	#else
		traverse_bvh_iter(ray, all->bvh, all->render_hb, all->render_hitbox);
	#endif
	if (isinf(ray->shape.t1))
		ray->color_ray = ray->color;
	else if (ray->shape.type == (t_obj_type)CYLINDER)
		ray->color_ray = ((t_cylinder *)(ray->shape.shape))->color;
	else if (ray->shape.type == (t_obj_type)SPHERE)
		ray->color_ray = ((t_sphere *)(ray->shape.shape))->color;
	else if (ray->shape.type == (t_obj_type)BOX)
		ray->color_ray = ((t_box *)(ray->shape.shape))->color;
	else if (ray->shape.type == (t_obj_type)PLANE)
		ray->color_ray = ((t_plane *)(ray->shape.shape))->color;
	ray->to_draw = 1;
}

void	traceray(t_ray *ray, t_all *all)
{
	init_ray(ray, all);
	closest_plane(ray, all->planes);
	#ifndef BVH
		closest_sphere(ray, all->spheres);
		closest_cylinder(ray, all->cylinders);
		closest_box(ray, all->boxes);
	#else
		traverse_bvh_iter(ray, all->bvh, all->render_hb, all->render_hitbox);
	#endif
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
	ray->color_ray.r = ray->color_shape.r * ray->color_diffuse.r + ray->color_specular.r;
	ray->color_ray.g = ray->color_shape.g * ray->color_diffuse.g + ray->color_specular.g;
	ray->color_ray.b = ray->color_shape.b * ray->color_diffuse.b + ray->color_specular.b;
}

void	traceray_reflection(t_ray *ray, t_all *all)
{
	t_rgb_f	ray_color_save;

	if (ray->reflection <= 0)
		return ;
	init_reflect_ray(ray, all, &ray_color_save);
	closest_plane(ray, all->planes);
	#ifndef BVH
		closest_sphere(ray, all->spheres);
		closest_cylinder(ray, all->cylinders);
		closest_box(ray, all->boxes);
	#else
		traverse_bvh_iter(ray, all->bvh, all->render_hb, 0);
	#endif
	if (isinf(ray->shape.t1))
		return ;
	ray->hit = scalar_multiplication_no_v(&ray->dir, ray->shape.t1);
	add_vectors(&ray->hit, &ray->start, &ray->hit);
	set_shapes(ray);
	if (dot_product(&ray->shape.normal, &ray->dir) > 0)
		ray->shape.normal = (t_vec){-ray->shape.normal.x,
			-ray->shape.normal.y, -ray->shape.normal.z};
	diffuse_light(ray, all, all->lights);
	ray->color_ray.r = ray->color_shape.r * ray->color_diffuse.r + ray->color_specular.r;
	ray->color_ray.g = ray->color_shape.g * ray->color_diffuse.g + ray->color_specular.g;
	ray->color_ray.b = ray->color_shape.b * ray->color_diffuse.b + ray->color_specular.b;
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

t_thread_mode	iter_rays_line_stop(t_all *all, t_threads *thread, void (*f)(t_ray *, t_all *))
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
			all->canvas.rays[index[0]][index[1]].y = index[1];
			all->canvas.rays[index[0]][index[1]].x = index[0];
			// if (all->render_hitbox)
			// 	_replace_s_px_on_render(all->render_hb, 0,
			// 		(t_point2d){real[1], real[0]}, all->canvas.pixel_values);
			f(&all->canvas.rays[index[0]][index[1]], all);
			real[1] += all->canvas.pixel_values;
			index[1] = real[1] + mi_pix;
		}
		if (get_thread_mode_pause(all, thread) == (t_thread_mode)STOP)
			return ((t_thread_mode)STOP);
		else if (thread->mode == (t_thread_mode)RESET)
			return ((t_thread_mode)RESET);
		real[0] += all->canvas.pixel_values;
		index[0] = real[0] + mi_pix;
	}
	return (((t_thread_mode)CONTINUE));
}

void	iter_rays(t_all *all, t_threads *thread, void (*f)(t_ray *, t_all *))
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
			all->canvas.rays[index[0]][index[1]].y = index[1];
			all->canvas.rays[index[0]][index[1]].x = index[0];
			f(&all->canvas.rays[index[0]][index[1]], all);
			real[1] += all->canvas.pixel_values;
			index[1] = real[1] + mi_pix;
		}
		real[0] += all->canvas.pixel_values;
		index[0] = real[0] + mi_pix;
	}
}

int	start_rays_thread_line(t_all *all, t_threads *thread)
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
			all->canvas.rays[index[0]][index[1]].y = index[1];
			all->canvas.rays[index[0]][index[1]].x = index[0];
			if (all->render_hitbox)
				_replace_s_px_on_render(all->render_hb, 0,
					(t_point2d){real[1], real[0]}, all->canvas.pixel_values);
			traceray(&all->canvas.rays[index[0]][index[1]], all);
			real[1] += all->canvas.pixel_values;
			index[1] = real[1] + mi_pix;
		}
		if (get_thread_mode_pause(all, thread) == (t_thread_mode)STOP)
			return ((t_thread_mode)STOP);
		else if (thread->mode == (t_thread_mode)RESET)
			return ((t_thread_mode)RESET);
		real[0] += all->canvas.pixel_values;
		index[0] = real[0] + mi_pix;
	}
	return (thread->mode);
}

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
			all->canvas.rays[index[0]][index[1]].y = index[1];
			all->canvas.rays[index[0]][index[1]].x = index[0];
			if (all->render_hitbox)
				_replace_s_px_on_render(all->render_hb, 0,
					(t_point2d){real[1], real[0]}, all->canvas.pixel_values);
			traceray(&all->canvas.rays[index[0]][index[1]], all);
			real[1] += all->canvas.pixel_values;
			index[1] = real[1] + mi_pix;
		}
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
