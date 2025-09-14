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
	printf("\t\t\t(%3.2f,%3.2f,%3.2f)     (%3.2f,%3.2f,%3.2f)\n", bvh->top[2].x,
		bvh->top[2].y, bvh->top[2].z, bvh->top[3].x, bvh->top[3].y,
		bvh->top[3].z);
	printf("                   \t      ____________________ \n");
	printf("                   \t    /                    /|\n");
	printf("                   \t   /                    / |\n");
	printf("                   \t  /                    /  |\n");
	printf("                   \t /                    /   |\n");
	printf("(%3.2f,%3.2f,%3.2f)\t/___________________ /(%3.2f,%3.2f,%3.2f)\n",
		bvh->top[0].x, bvh->top[0].y, bvh->top[0].z, bvh->top[1].x,
		bvh->top[1].y, bvh->top[1].z);
	printf("                   \t|                   |     |\n");
	printf("                   \t|                   |     |\n");
	printf("                   \t|                   |     |\n");
	printf("                   \t|                   |    / (%3.2f,%3.2f,%3.2f) \
		\n", bvh->bottom[3].x, bvh->bottom[3].y, bvh->bottom[3].z);
	printf("                   \t|                   |   /\n");
	printf("                   \t|                   |  /\n");
	printf("                   \t|                   | /\n");
	printf("                   \t|___________________|/\n");
	printf("             (%3.2f,%3.2f,%3.2f)     (%3.2f,%3.2f,%3.2f)\n\n",
		bvh->bottom[0].x, bvh->bottom[0].y, bvh->bottom[0].z,
		bvh->bottom[1].x, bvh->bottom[1].y, bvh->bottom[1].z);
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
		a.x += 0.1;
	if (a.y == b.y)
		a.y += 0.1;
	if (a.z == b.z)
		a.z += 0.1;
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

int	check_val(double a)
{
	if (a >= 1e-6)
		return (1);
	return (0);
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
	return (t_values[1] >= t_values[0] && t_values[1] >= 1e-6);
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
		t[0] = (box->box.bottom[0].x - ray->start.x) / ray->dir.x;
		t[1] = (box->box.top[3].x - ray->start.x) / ray->dir.x;
		entry = fmin(t[0], t[1]);
		if (entry > t_values[0])
			best_normal = (t_vec){1, 0, 0};
		t_values[0] = fmax(t_values[0], entry);
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (ray->dir.y != 0.0f)
	{
		t[0] = (box->box.bottom[0].y - ray->start.y) / ray->dir.y;
		t[1] = (box->box.top[3].y - ray->start.y) / ray->dir.y;
		entry = fmin(t[0], t[1]);
		if (entry > t_values[0])
			best_normal = (t_vec){0, 1, 0};
		t_values[0] = fmax(t_values[0], entry);
		t_values[1] = fmin(t_values[1], fmax(t[0], t[1]));
	}
	if (ray->dir.z != 0.0f)
	{
		t[0] = (box->box.bottom[0].z - ray->start.z) / ray->dir.z;
		t[1] = (box->box.top[3].z - ray->start.z) / ray->dir.z;
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
	return (t_values[1] >= t_values[0] && t_values[1] >= 1e-6);
}

void	closest_box(t_ray *ray, t_box *boxes)
{
	while (boxes)
	{
		intersect_box(ray, boxes);
		boxes = boxes->next;
	}
}

int	box_on_path(t_ray *ray, t_box *boxes, t_vec light_dir)
{
	while (boxes)
	{
		if(shadow_intersect_bvh(ray, &boxes->box, light_dir))
			return (1);
		boxes = boxes->next;
	}
	return (0);
}
