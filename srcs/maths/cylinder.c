#include "miniRT.h"

// || (O + tD) − C − (((O+tD)−C)⋅V)V ||^2 − r^2 = 0
// CO = O - C
// || (CO + tD) - ((CO + tD) * V)V ||^2 - r^2 = 0
// tmp = (CO * V)V
// CO = CO - tmp
// d = || D - (D * V)V ||^2

// a = d * d
// b = 2(CO * d)
// c = CO * CO - r^2
static void	set_ts(double t, t_ray *ray, t_cylinder *cylinder)
{
	t_vec	p;
	t_vec	v;
	double	mag;

	if (t >= 1e-6 && (isinf(ray->shape.t1) || t < ray->shape.t1))
	{
		add_vectors(&ray->start, scalar_multiplication(&ray->dir, t, &p), &p);
		p = sub_vectors_no_v(&p, &cylinder->coord);
		mag = dot_product(&p, &cylinder->vec);
		if (mag < 0 || mag > cylinder->height || isnan(mag) || isinf(mag))
			return ;
		v = scalar_multiplication_no_v(&cylinder->vec, mag);
		cylinder->normal = sub_vectors_no_v(&p, &v);
		cylinder->normal_mag = vec_magnitude(&cylinder->normal);
		ray->shape.t1 = t;
		ray->shape.shape = cylinder;
		ray->shape.type = CYLINDER;
		return ;
	}
}

void	intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_vec	co;
	t_vec	tmp;
	t_vec	d;
	double	A;
	double	B;
	double	C;
	double	discriminant;
	double	t;

	co = sub_vectors_no_v(&ray->start, &cylinder->coord);
	tmp = scalar_multiplication_no_v(&cylinder->vec, dot_product(&co, &cylinder->vec));
	co = sub_vectors_no_v(&co, &tmp);
	tmp = scalar_multiplication_no_v(&cylinder->vec, dot_product(&ray->dir, &cylinder->vec));
	d = sub_vectors_no_v(&ray->dir, &tmp);
	A = dot_product(&d, &d);
	B = 2 * dot_product(&d, &co);
	C = dot_product(&co, &co) - cylinder->radius_squared;
	discriminant = B * B - (4 * A * C);
	if (discriminant < 0)
		return ;
	B = -B;
	A = 2 * A;
	discriminant = sqrt(discriminant);
	t = (B - discriminant) / A;
	set_ts(t, ray, cylinder);
	t = (B + discriminant) / A;
	set_ts(t, ray, cylinder);
}

void	closest_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	while (cylinder)
	{
		intersect_cylinder(ray, cylinder);
		cylinder = cylinder->next;
	}
}
