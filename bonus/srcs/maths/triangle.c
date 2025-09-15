#include "miniRT.h"

static void	set_ts(double t, t_ray *ray, t_face *face, t_vec *normale)
{
	if (t >= 1e-6 && (isinf(ray->shape.t1) || t < ray->shape.t1))
	{
		// tri_lib()->put_pixel_to_render(__get_all()->render_hb, (t_argb){.a=0.25, .r=255,
		// .g=0,.b=0}, ray->y, ray->x);
		norm_vectors(normale, vec_magnitude(normale), normale);
		ray->shape.t1 = t;
		ray->shape.shape = face;
		ray->shape.type = TRIANGLE;
		ray->shape.normal = *normale;
		return ;
	}
}

// void	intersect_triangle(t_ray *ray, t_face *face)
// {
// 	t_vec e[2];
	
	
// 	t_vec		t;
// 	t_vec 		p;
// 	double		det;
// 	t_vec		q;
// 	double		u;
// 	double		v;
// 	double		lil_t;
	
// 	e[0]= sub_vectors_no_v(face->vertices[1], face->vertices[0]); //e1 = v2 - v1
// 	e[1] = sub_vectors_no_v(face->vertices[2], face->vertices[0]); //e2 = v3 - v1
// 	t = sub_vectors_no_v(&ray->start, face->vertices[0]); 
// 	cross_product(&ray->dir, &e[1], &p);
// 	det = dot_product(&e[0], &p);
// 	if (fabs(det) < 1e-6)
// 		return ;
// 	det = 1.0f / det;
// 	u = dot_product(&t, &p) * det;
// 	if (u < 0.0 || u > 1.0)
// 	    return;
// 	cross_product(&t, &e[0], &q);
// 	v = dot_product(&ray->dir, &q) * det;
// 	if (v < 1e-6)
// 	    return;
// 	lil_t = dot_product(&e[1], &q) * det;
// 	set_ts(lil_t, ray, face, cross_product(&e[0], &e[1], &t));
// }

void intersect_triangle(t_ray *ray, t_face *face)
{
	t_vec e[2];
	t_vec d;
	t_vec p;
	double det;
    t_vec q;
    double u, v, t;

	e[0] = sub_vectors_no_v(face->vertices[1], face->vertices[0]);
    e[1] = sub_vectors_no_v(face->vertices[2], face->vertices[0]);
	p = sub_vectors_no_v(&ray->start, face->vertices[0]);
	cross_product(&ray->dir, &e[1], &d);
    det = dot_product(&e[0], &d);
	if (fabs(det) < 1e-6 && fabs(det) > -1e-6)
		return;
	u = dot_product(&p, &d) / det;
	if (u < 0 || u > 1)
		return ;
	cross_product(&p, &e[0], &q);
	v = dot_product(&ray->dir, &q) / det;
	if (v < 1e-6 || u + v > 1)
		return ;
	t = dot_product(&e[1], &q) / det;
	if (t < 1e-6)
		return ;
	set_ts(t, ray, face, &q);
}

void intersect_triangle_quad(t_ray *ray, t_face *face, t_inter *inter)
{
	t_vec e[2];
	t_vec d;
	t_vec p;
	double det;
	t_vec q;
	double u, v, t;

	e[0] = sub_vectors_no_v(face->vertices[1], face->vertices[0]);
	e[1] = sub_vectors_no_v(face->vertices[2], face->vertices[0]);
	cross_product(&ray->dir, &e[1], &d);
	det = dot_product(&e[0], &d);
	if (fabs(det) < 1e-6)
		return;
	p = sub_vectors_no_v(&ray->start, face->vertices[0]);
	u = dot_product(&p, &d) / det;
	if (u < 0.0f || u > 1)
		return ;
	cross_product(&p, &e[0], &q);
	v = dot_product(&ray->dir, &q) / det;
	if (v < 0.0f || u + v > 1)
		return ;
	t = dot_product(&e[1], &q) / det;
	if (t < -1e-6)
		return ;
	if (t > inter->t)
		return ;
	inter->t = t;
	cross_product(&e[0], &e[1], &inter->normale);
	inter->found += 1;
}

void intersect_quad(t_ray *ray, t_face *face)
{
	t_face	new;
	t_inter	inter;

	inter.found = 0;
	inter.t = INFINITY;
	new.vertices[0] = face->vertices[0];
	new.vertices[1] = face->vertices[1];
	new.vertices[2] = face->vertices[2];
	intersect_triangle_quad(ray, &new, &inter);
	if (face->vertices[3])
	{
		new.vertices[0] = face->vertices[2];
		new.vertices[1] = face->vertices[3];
		new.vertices[2] = face->vertices[0];
		intersect_triangle_quad(ray, &new, &inter);
	}
	if (!inter.found)
			return ;
	set_ts(inter.t, ray, face, &inter.normale);
}