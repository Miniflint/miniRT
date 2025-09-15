#include "miniRT.h"

static void	set_ts(double t, t_ray *ray, t_face *face, t_vec *normale)
{
	if (t >= 1e-6 && (isinf(ray->shape.t1) || t < ray->shape.t1))
	{
		norm_vectors(normale, vec_magnitude(normale), normale);
		ray->shape.t1 = t;
		ray->shape.shape = face;
		ray->shape.type = TRIANGLE;
		ray->shape.normal = *normale;
		return ;
	}
}

void	intersect_triangle_quad(t_ray *ray, t_inter *inter)
{
	t_vec	e[2];
	t_vec	d;
	double	t;

	e[0] = sub_vectors_no_v(inter->face->vertices[1], inter->face->vertices[0]);
	e[1] = sub_vectors_no_v(inter->face->vertices[2], inter->face->vertices[0]);
	cross_product(&ray->dir, &e[1], &d);
	inter->det = dot_product(&e[0], &d);
	if (fabs(inter->det) < 1e-6)
		return ;
	inter->p = sub_vectors_no_v(&ray->start, inter->face->vertices[0]);
	inter->u = dot_product(&inter->p, &d) / inter->det;
	if (inter->u < 0.0f || inter->u > 1)
		return ;
	cross_product(&inter->p, &e[0], &inter->q);
	inter->v = dot_product(&ray->dir, &inter->q) / inter->det;
	if (inter->v < 0.0f || inter->u + inter->v > 1)
		return ;
	t = dot_product(&e[1], &inter->q) / inter->det;
	if (t < -1e-6 || t > inter->t)
		return ;
	inter->t = t;
	cross_product(&e[0], &e[1], &inter->normale);
	inter->found += 1;
}

void	intersect_quad(t_ray *ray, t_face *face)
{
	t_face	new;
	t_inter	inter;

	inter.found = 0;
	inter.t = INFINITY;
	inter.face = face;
	new.vertices[0] = face->vertices[0];
	new.vertices[1] = face->vertices[1];
	new.vertices[2] = face->vertices[2];
	inter.face = &new;
	intersect_triangle_quad(ray, &inter);
	if (face->vertices[3])
	{
		new.vertices[0] = face->vertices[0];
		new.vertices[1] = face->vertices[2];
		new.vertices[2] = face->vertices[3];
		inter.face = &new;
		intersect_triangle_quad(ray, &inter);
	}
	if (!inter.found)
		return ;
	set_ts(inter.t, ray, face, &inter.normale);
}

int	shadow_intersect_triangle_quad(t_ray *ray, t_inter *inter,
	t_vec light_dir, double light_length)
{
	t_vec	e[2];
	t_vec	d;
	double	t;

	e[0] = sub_vectors_no_v(inter->face->vertices[1], inter->face->vertices[0]);
	e[1] = sub_vectors_no_v(inter->face->vertices[2], inter->face->vertices[0]);
	cross_product(&light_dir, &e[1], &d);
	inter->det = dot_product(&e[0], &d);
	if (fabs(inter->det) < 1e-6)
		return (0);
	inter->p = sub_vectors_no_v(&ray->hit, inter->face->vertices[0]);
	inter->u = dot_product(&inter->p, &d) / inter->det;
	if (inter->u < 0.0f || inter->u > 1)
		return (0);
	cross_product(&inter->p, &e[0], &inter->q);
	inter->v = dot_product(&light_dir, &inter->q) / inter->det;
	if (inter->v < 0.0f || inter->u + inter->v > 1)
		return (0);
	t = dot_product(&e[1], &inter->q) / inter->det;
	if (t < -1e-6 || t > inter->t || t > light_length)
		return (0);
	inter->t = t;
	inter->found += 1;
	return (1);
}

int	shadow_intersect_quad(t_ray *ray, t_face *face,
	t_vec light_dir, double light_length)
{
	t_face	new;
	t_inter	inter;

	inter.found = 0;
	inter.t = INFINITY;
	inter.face = face;
	new.vertices[0] = face->vertices[0];
	new.vertices[1] = face->vertices[1];
	new.vertices[2] = face->vertices[2];
	inter.face = &new;
	shadow_intersect_triangle_quad(ray, &inter, light_dir, light_length);
	if (face->vertices[3])
	{
		new.vertices[0] = face->vertices[0];
		new.vertices[1] = face->vertices[2];
		new.vertices[2] = face->vertices[3];
		inter.face = &new;
		shadow_intersect_triangle_quad(ray, &inter, light_dir, light_length);
	}
	if (!inter.found)
		return (0);
	if (inter.t > light_length)
		return (0);
	return (1);
}
