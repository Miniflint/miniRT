#include "miniRT.h"

int	shadow_intersect_cylinder(t_ray *ray,
		t_cylinder *cylinder, t_vec light_dir, double light_lenght)
{
	t_vec	co;
	t_vec	tmp;
	t_vec	d;
	t_quad	q;

	co = sub_vectors_no_v(&ray->hit, &cylinder->coord);
	tmp = scalar_multiplication_no_v(&cylinder->vec,
			dot_product(&co, &cylinder->vec));
	co = sub_vectors_no_v(&co, &tmp);
	tmp = scalar_multiplication_no_v(&cylinder->vec,
			dot_product(&light_dir, &cylinder->vec));
	d = sub_vectors_no_v(&light_dir, &tmp);
	q.a = dot_product(&d, &d);
	q.b = 2 * dot_product(&d, &co);
	q.c = dot_product(&co, &co) - cylinder->radius_squared;
	q.discriminant = q.b * q.b - (4 * q.a * q.c);
	if (q.discriminant < 0)
		return (0);
	q.b = -q.b;
	q.a = 2 * q.a;
	q.discriminant = sqrt(q.discriminant);
	q.t = (q.b - q.discriminant) / q.a;
	return (check_t(q, ray, cylinder, (t_light_vec){light_dir, light_lenght}));
}

int	shadow_intersect_sphere(t_ray *ray, t_sphere *sphere,
		t_vec light_dir, double light_lenght)
{
	double			disciminant;
	const t_vec		co = sub_vectors_no_v(&ray->hit, &sphere->coord);
	const double	b = 2 * dot_product((t_vec *)&co, &light_dir);
	const double	c = dot_product((t_vec *)&co, (t_vec *)&co)
		- sphere->radius_squared;
	double			t;

	disciminant = b * b - 4.0 * c;
	if (disciminant < 0)
		return (0);
	disciminant = sqrt(disciminant);
	t = (-b - disciminant) / 2.0;
	if ((t >= 1e-6 && t < light_lenght))
		return (1);
	t = (-b + disciminant) / 2.0;
	if ((t >= 1e-6 && t < light_lenght))
		return (1);
	return (0);
}

int	shadow_intersect_plane(t_ray *ray, t_plane *plane,
		t_vec light_dir, double light_lenght)
{
	double	dot;
	double	t;
	t_vec	new_vec;

	dot = dot_product(&plane->vec, &light_dir);
	if (dot == 0)
		return (0);
	sub_vectors(&ray->hit, &plane->coord, &new_vec);
	t = -dot_product(&plane->vec, &new_vec) / dot;
	if (t >= 1e-6 && t < light_lenght)
		return (1);
	return (0);
}
