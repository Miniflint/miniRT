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

void	intersect_triangle(t_ray *ray, t_face *face)
{
	t_vec e[2];
	
	
	t_vec		t;
	t_vec 		p;
	double		det;
	t_vec		q;
	double		u;
	double		v;
	double		lil_t;
	
	e[0]= sub_vectors_no_v(face->vertices[1], face->vertices[0]);
	e[1] = sub_vectors_no_v(face->vertices[2], face->vertices[0]);
	t = sub_vectors_no_v(&ray->start, face->vertices[0]);
	cross_product(&ray->dir, &e[1], &p);
	det = dot_product(&e[0], &p);
	if (fabs(det) < 1e-6)
		return ;
	det = 1.0f / det;
	u = dot_product(&t, &p) * det;
	if (u < 0.0 || u > 1.0)
	    return;
	cross_product(&t, &e[0], &q);
	v = dot_product(&ray->dir, &q) * det;
	if (v < 0.0 || v > 1.0)
	    return;
	lil_t = dot_product(&e[1], &q) * det;
	if (lil_t < 1e-6)
		return ;
	set_ts(lil_t, ray, face, cross_product(&e[0], &e[1], &t));
}