#include "miniRT.h"

void	swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	print_pts(t_vec v)
{
	printf("P(%f,%f,%f)\n", v.x, v.y, v.z);
}

void	print_box(t_bvh *bvh)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		print_pts(bvh->bottom[i]);
		print_pts(bvh->top[i]);
		i++;
	}
}

t_bvh	create_box(t_vec a, t_vec b)
{
	t_bvh	new;
	t_vec	tmp;

	if (b.y - a.y < 0)
	{
		tmp = a;
		a = b;
		b = tmp;
	}
	new.bottom[0] = (t_vec){.x = a.x, .y = a.y, .z = a.z};
	new.bottom[1] = (t_vec){.x = b.x, .y = a.y, .z = a.z};
	new.bottom[2] = (t_vec){.x = a.x, .y = b.y, .z = a.z};
	new.bottom[3] = (t_vec){.x = b.x, .y = b.y, .z = a.z};
	new.top[0] = (t_vec){.x = a.x, .y = a.y, .z = b.z};
	new.top[1] = (t_vec){.x = b.x, .y = a.y, .z = b.z};
	new.top[2] = (t_vec){.x = a.x, .y = b.y, .z = b.z};
	new.top[3] = (t_vec){.x = b.x, .y = b.y, .z = b.z};
	return (new);
}

int	bvh_on_path(t_ray *ray, t_box *box)
{
	double	t[2];
	double	t_values[2];

	t_values[0] = -INFINITY;
	t_values[1] = INFINITY;
	if (ray->dir.x != 0.0f)
	{
		t[0] = (box->box.bottom[0].x - ray->start.x) / ray->dir.x;
		t[1] = (box->box.top[3].x - ray->start.x) / ray->dir.x;
		t_values[0] = fmax(t_values[0], fmin(t[0], t[1]));
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (ray->dir.y != 0.0f)
	{
		t[0] = (box->box.bottom[0].y - ray->start.y) / ray->dir.y;
		t[1] = (box->box.top[3].y - ray->start.y) / ray->dir.y;
		t_values[0] = fmax(t_values[0], fmin(t[0], t[1]));
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (ray->dir.z != 0.0f)
	{
		t[0] = (box->box.bottom[0].z - ray->start.z) / ray->dir.z;
		t[1] = (box->box.top[3].z - ray->start.z) / ray->dir.z;
		t_values[0] = fmax(t_values[0], fmin(t[0], t[1]));
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	return (t_values[1] >= t_values[0] && t_values[1] > 0.0f);
}

static int	set_ts(double t, t_ray *ray, t_box *box, t_vec xyz)
{
	if (t >= 1e-6 && (isinf(ray->shape.t1) || t < ray->shape.t1))
	{
		ray->shape.t1 = t;
		scalar_multiplication(&ray->dir, t, &ray->hit);
		ray->shape.shape = (void *)box;
		ray->shape.normal = xyz;
		ray->shape.type = BOX;
	}
	return (0);
}

void	intersect_box(t_ray *ray, t_box *box)
{
	double	t[2];
	double	t_values[2];
	double	entry;
	t_vec	best_normal;

	t_values[0] = -INFINITY;
	t_values[1] = INFINITY;
	if (ray->dir.x != 0.0f)
	{
		t[0] = (box->box.a->x - ray->start.x) / ray->dir.x;
		t[1] = (box->box.b->x - ray->start.x) / ray->dir.x;
		entry = fmin(t[0], t[1]);
		if (entry > t_values[0])
			best_normal = (t_vec){1, 0, 0};
		t_values[0] = fmax(t_values[0], entry);
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (ray->dir.y != 0.0f)
	{
		t[0] = (box->box.a->y - ray->start.y) / ray->dir.y;
		t[1] = (box->box.b->y - ray->start.y) / ray->dir.y;
		entry = fmin(t[0], t[1]);
		if (entry > t_values[0])
			best_normal = (t_vec){0, 1, 0};
		t_values[0] = fmax(t_values[0], entry);
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (ray->dir.z != 0.0f)
	{
		t[0] = (box->box.a->z - ray->start.z) / ray->dir.z;
		t[1] = (box->box.b->z - ray->start.z) / ray->dir.z;
		entry = fmin(t[0], t[1]);
		if (entry > t_values[0])
			best_normal = (t_vec){0, 0, 1};
		t_values[0] = fmax(t_values[0], entry);
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (t_values[1] >= t_values[0] && t_values[1] > 0.0f)
	{
		if (t_values[0] > t_values[1])
			set_ts(t_values[1], ray, box, best_normal);
		else if (t_values[1] > t_values[0])
			set_ts(t_values[0], ray, box, best_normal);
	}
}
int	intersect_hitbox(t_ray *ray, t_bvh *box)
{
	double	t[2];
	double	t_values[2];
	double	entry;

	t_values[0] = -INFINITY;
	t_values[1] = INFINITY;
	if (ray->dir.x != 0.0f)
	{
		t[0] = (box->bottom[0].x - ray->start.x) / ray->dir.x;
		t[1] = (box->top[3].x - ray->start.x) / ray->dir.x;
		entry = fmin(t[0], t[1]);
		t_values[0] = fmax(t_values[0], entry);
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (ray->dir.y != 0.0f)
	{
		t[0] = (box->bottom[0].y - ray->start.y) / ray->dir.y;
		t[1] = (box->top[3].y - ray->start.y) / ray->dir.y;
		entry = fmin(t[0], t[1]);
		t_values[0] = fmax(t_values[0], entry);
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (ray->dir.z != 0.0f)
	{
		t[0] = (box->bottom[0].z - ray->start.z) / ray->dir.z;
		t[1] = (box->top[3].z - ray->start.z) / ray->dir.z;
		entry = fmin(t[0], t[1]);
		t_values[0] = fmax(t_values[0], entry);
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	return (t_values[1] >= t_values[0] && t_values[1] > 0.0f);
}

int	shadow_intersect_hitbox(t_ray *ray, t_bvh *box, t_vec light_dir, double light_length)
{
	double	t[2];
	double	t_values[2];
	double	entry;

	t_values[0] = -INFINITY;
	t_values[1] = INFINITY;
	if (light_dir.x != 0.0f)
	{
		t[0] = (box->bottom[0].x - ray->hit.x) / light_dir.x;
		t[1] = (box->top[3].x - ray->hit.x) / light_dir.x;
		entry = fmin(t[0], t[1]);
		t_values[0] = fmax(t_values[0], entry);
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (light_dir.y != 0.0f)
	{
		t[0] = (box->bottom[0].y - ray->hit.y) / light_dir.y;
		t[1] = (box->top[3].y - ray->hit.y) / light_dir.y;
		entry = fmin(t[0], t[1]);
		t_values[0] = fmax(t_values[0], entry);
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (light_dir.z != 0.0f)
	{
		t[0] = (box->bottom[0].z - ray->hit.z) / light_dir.z;
		t[1] = (box->top[3].z - ray->hit.z) / light_dir.z;
		entry = fmin(t[0], t[1]);
		t_values[0] = fmax(t_values[0], entry);
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (t_values[1] >= t_values[0] && t_values[1] > 0.0f)
		if (t_values[0] > 0 && t_values[0] < light_length)
			return (1);
	return (0);}

void	closest_box(t_ray *ray, t_box *boxes)
{
	while (boxes)
	{
		intersect_box(ray, boxes);
		boxes = boxes->next;
	}
}
