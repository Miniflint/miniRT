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

unsigned char	intersect_box(t_ray *ray, t_bvh *bvh)
{
	double	t[2];
	double	inv_d;
	double	t_values[2];

	t_values[0] = -INFINITY;
	t_values[1] = INFINITY;
	if (ray->dir.x != 0.0f)
	{
		inv_d = 1.0f / ray->dir.x;
		t[0] = (bvh->a->x - ray->start.x) * inv_d;
		t[1] = (bvh->b->x - ray->start.x) * inv_d;
		if (inv_d < 0.0f)
			swap(&t[0], &t[1]);
		t_values[0] = fmax(t_values[0], t[0]);
		t_values[1] = fmin(t_values[1], t[1]);
	}
	if (ray->dir.y != 0.0f)
	{
		inv_d = 1.0f / ray->dir.y;
		t[0] = (bvh->a->y - ray->start.y) * inv_d;
		t[1] = (bvh->b->y - ray->start.y) * inv_d;
		if (inv_d < 0.0f)
			swap(&t[0], &t[1]);
		t_values[0] = fmax(t_values[0], t[0]);
		t_values[1] = fmin(t_values[1], t[1]);
	}
	if (ray->dir.z != 0.0f)
	{
		inv_d = 1.0f / ray->dir.z;
		t[0] = (bvh->a->z - ray->start.z) * inv_d;
		t[1] = (bvh->b->z - ray->start.z) * inv_d;
		if (inv_d < 0.0f)
			swap(&t[0], &t[1]);
		t_values[0] = fmax(t_values[0], t[0]);
		t_values[1] = fmin(t_values[1], t[1]);
	}
	return (t_values[1] >= t_values[0] && t_values[1] > 0.0f);
}
