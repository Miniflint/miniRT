#include "miniRT.h"
#include "tri_lib.h"

void	closest_plane(t_ray *ray, t_plane *plane)
{
	while (plane)
	{
		intersect_plane(ray, plane);
		plane = plane->next;
	}
}

#ifdef SSAA

void	init_ray(t_ray *ray, t_all *all)
{
	ray->end = 0;
	if (all->render_hitbox && !(ray->x % 2) && !(ray->y % 2))
		_replace_pixel_on_render(all->render_hb, 0, ray->y >> 1, ray->x >> 1);
	ray->color_shape = (t_rgb_f){0, 0, 0};
	ray->color_diffuse = (t_rgb_f){0, 0, 0};
	ray->color_specular = (t_rgb_f){0, 0, 0};
	ray->shape.type = CAMERA;
	ray->shape.shape = NULL;
	ray->reflection = (t_rgb_f){1, 1, 1};
	ray->shape.t1 = INFINITY;
}

#else

void	init_ray(t_ray *ray, t_all *all)
{
	ray->end = 0;
	if (all->render_hitbox)
		_replace_s_px_on_render(all->render_hb, 0,
			(t_point2d){ray->y, ray->x}, all->canvas.pixel_values);
	ray->color_shape = (t_rgb_f){0, 0, 0};
	ray->color_diffuse = (t_rgb_f){0, 0, 0};
	ray->color_specular = (t_rgb_f){0, 0, 0};
	ray->shape.type = CAMERA;
	ray->shape.shape = NULL;
	ray->reflection = (t_rgb_f){1, 1, 1};
	ray->shape.t1 = INFINITY;
}

#endif

void	init_reflect_ray(t_ray *ray, t_all *all)
{
	t_vec	vec;

	(void)all;
	ray->color_shape = (t_rgb_f){0, 0, 0};
	ray->color_diffuse = (t_rgb_f){0, 0, 0};
	ray->color_specular = (t_rgb_f){0, 0, 0};
	add_vectors(&ray->hit, scalar_multiplication(&ray->shape.normal,
			1e-6, &vec), &ray->start);
	vec = scalar_multiplication_no_v(&ray->shape.normal, 2.0
			* dot_product(&ray->shape.normal, &ray->dir));
	ray->dir = sub_vectors_no_v(&ray->dir, &vec);
	norm_vectors(&ray->dir, vec_magnitude(&ray->dir), &ray->dir);
	ray->shape.type = CAMERA;
	ray->shape.shape = NULL;
	ray->shape.t1 = INFINITY;
}

static void	if_leaf_internal(t_ray *ray, t_hitbox *curr, t_queue *q, t_threads *thread)
{
	if (curr->node_type == LEAF)
	{
		if (!__get_all()->render_on)
			return ;
		if (curr->type == SPHERE)
			intersect_ray_sphere(ray, (t_sphere *)curr->shape);
		else if (curr->type == CYLINDER)
			intersect_cylinder(ray, (t_cylinder *)curr->shape, thread);
		else if (curr->type == BOX)
			intersect_box(ray, (t_box *)curr->shape);
		else if (curr->type == TRIANGLE)
			intersect_quad(ray, (t_face *)curr->shape, thread);
	}
	else
	{
		if (curr->type == OBJECT)
			thread->material = ((t_object *)curr->shape)->material;
		if (curr->left)
			queue_push(q, curr->left);
		if (curr->right)
			queue_push(q, curr->right);
	}
}

#ifdef SSAA

void	traverse_bvh_iter(t_ray *ray, t_all *all, t_threads *t, int hb)
{
	t_queue			q;
	t_hitbox		*curr;
	const t_tri_lib	*lib = tri_lib();

	queue_push(&thread->queue, all->bvh);
	while (!queue_is_empty(&thread->queue))
	{
		curr = queue_pop(&thread->queue);
		if (!curr || !intersect_hitbox(ray, &curr->box))
			continue ;
		if (hb && !(ray->x % 2) && !(ray->y % 2))
			lib->put_pixel_to_render(all->render_hb, (t_argb){.a = 0.25,
				.r = 255, .g = 255, .b = 255}, ray->y >> 1, ray->x >> 1);
		if_leaf_internal(ray, curr, &thread->queue, t);
	}
}

#else

void	traverse_bvh_iter(t_ray *ray, t_all *all, __attribute_maybe_unused__ t_threads *thread, int hb)
{
	t_hitbox		*curr;
	const t_tri_lib	*lib = tri_lib();

	queue_push(&thread->queue, all->bvh);
	while (!queue_is_empty(&thread->queue))
	{
		curr = queue_pop(&thread->queue);
		if (!curr || !intersect_hitbox(ray, &curr->box))
			continue ;
		if (hb && !(ray->x % 2) && !(ray->y % 2))
			lib->put_pixel_to_render(all->render_hb, (t_argb){.a = 0.25,
				.r = 255, .g = 255, .b = 255}, ray->y >> 1, ray->x >> 1);
		if_leaf_internal(ray, curr, &thread->queue, thread);
	}
}

#endif

void	get_local_color(t_ray *ray, t_all *all, t_threads *thread)
{
	t_rgb_f	reflection;

	if (isinf(ray->shape.t1) || ray->end)
	{
		ray->end = 1;
		return ;
	}
	ray->hit = scalar_multiplication_no_v(&ray->dir, ray->shape.t1);
	add_vectors(&ray->hit, &ray->start, &ray->hit);
	set_shapes(ray, thread);
	if (dot_product(&ray->shape.normal, &ray->dir) > 0)
		ray->shape.normal = (t_vec){-ray->shape.normal.x,
			-ray->shape.normal.y, -ray->shape.normal.z};
	diffuse_light(ray, all, thread, all->lights);
	reflection = ray->shape.material.reflection;
	ray->color_ray.r += (ray->color_shape.r * ray->color_diffuse.r
			+ ray->color_specular.r) * (1.0 - reflection.r) * ray->reflection.r;
	ray->color_ray.g += (ray->color_shape.g * ray->color_diffuse.g
			+ ray->color_specular.g) * (1.0 - reflection.g) * ray->reflection.g;
	ray->color_ray.b += (ray->color_shape.b * ray->color_diffuse.b
			+ ray->color_specular.b) * (1.0 - reflection.b) * ray->reflection.b;
	ray->reflection.r *= reflection.r;
	ray->reflection.g *= reflection.g;
	ray->reflection.b *= reflection.b;
	ray->to_draw = 1;
	ray->end = ray->reflection.r <= 0
		&& ray->reflection.g <= 0 && ray->reflection.b <= 0;
}

void	init_color_ray(t_ray *ray)
{
	if (!ray->end)
		ray->color_ray = (t_rgb_f){0, 0, 0};
}

void	get_closest_color(t_ray *ray, t_all *all, t_threads *thread)
{
	init_ray(ray, all);
	closest_plane(ray, all->planes);
	traverse_bvh_iter(ray, all, thread, all->render_hitbox);
	if (isinf(ray->shape.t1))
		ray->end = 1;
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

void	traceray_reflection(t_ray *ray, t_all *all, t_threads *thread)
{
	if (ray->end)
		return ;
	init_reflect_ray(ray, all);
	closest_plane(ray, all->planes);
	traverse_bvh_iter(ray, all, thread, 0);
	get_local_color(ray, all, thread);
}

#ifdef SSAA

t_thread_mode	iter_rays_line_stop(t_all *all,
	t_threads *thread,
	void (*f)(t_ray *, t_all *)
)
{
	int				i;
	int				j;

	i = thread->start;
	while (i < thread->end)
	{
		j = 0;
		while (j < all->win_width)
		{
			all->canvas.rays[i][j].y = j;
			all->canvas.rays[i][j].x = i;
			f(&all->canvas.rays[i][j], all, thread);
			++j;
		}
		if (get_thread_mode_pause(all, thread) == (t_thread_mode)STOP)
			return ((t_thread_mode)STOP);
		else if (thread->mode == (t_thread_mode)RESET)
			return ((t_thread_mode)RESET);
		++i;
	}
	return (((t_thread_mode)CONTINUE));
}

void	iter_rays(t_all *all, t_threads *thread, void (*f)(t_ray *))
{
	int	i;
	int	j;

	i = thread->start;
	while (i < thread->end)
	{
		j = 0;
		while (j < all->win_width)
		{
			f(&all->canvas.rays[i][j]);
			++j;
		}
		++i;
	}
}

#else

void	if_iter_rays_line(t_all *all,
	int index[2],
	int real[2]
)
{
	if (index[1] >= all->win_width)
		index[1] = all->win_width - 1;
	all->canvas.rays[index[0]][index[1]].y = index[1];
	all->canvas.rays[index[0]][index[1]].x = index[0];
	real[1] += all->canvas.pixel_values;
}

t_thread_mode	iter_rays_line_stop(t_all *all,
	t_threads *thread,
	void (*f)(t_ray *, t_all *, t_threads *)
)
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
		if (index[0] >= thread->end)
			index[0] = thread->end - 1;
		while (real[1] < all->win_width)
		{
			if_iter_rays_line(all, index, real);
			f(&all->canvas.rays[index[0]][index[1]], all, thread);
			index[1] = real[1] + mi_pix;
		}
		if (get_thread_mode_pause(all, thread) == (t_thread_mode)STOP
			|| thread->mode == (t_thread_mode)RESET)
			return (thread->mode);
		real[0] += all->canvas.pixel_values;
		index[0] = real[0] + mi_pix;
	}
	return (((t_thread_mode)CONTINUE));
}

void	iter_rays(t_all *all, t_threads *thread, void (*f)(t_ray *))
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
		if (index[0] >= thread->end)
			index[0] = thread->end - 1;
		while (real[1] < all->win_width)
		{
			if (index[1] >= all->win_width)
				index[1] = all->win_width - 1;
			f(&all->canvas.rays[index[0]][index[1]]);
			real[1] += all->canvas.pixel_values;
			index[1] = real[1] + mi_pix;
		}
		real[0] += all->canvas.pixel_values;
		index[0] = real[0] + mi_pix;
	}
}

#endif
