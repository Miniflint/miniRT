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

	//printf("ray->dir: ");
	// print_vec(ray->dir);
	//printf("ray->start: ");
	// print_vec(ray->start);
	//printf("vertice[0]: ");
	// print_vec((face->vertices[0])[0]);
	//printf("vertice[1]: ");
	// print_vec((face->vertices[1])[0]);
	//printf("vertice[2]: ");
	// print_vec((face->vertices[2])[0]);
	// Calculate the edges of the triangle
	e[0] = sub_vectors_no_v(face->vertices[1], face->vertices[0]); // e1 = v2 - v1
    e[1] = sub_vectors_no_v(face->vertices[2], face->vertices[0]); // e2 = v3 - v1
	//printf("e[0]: ");
	// print_vec(e[0]);
	//printf("e[1]: ");
	// print_vec(e[1]);

	// Vector from ray origin to vertex V1
	p = sub_vectors_no_v(&ray->start, face->vertices[0]);
	//printf("p: ");
	// print_vec(p);

	// Calculate the determinant
	cross_product(&ray->dir, &e[1], &d); // d = ray->direction × e2
	//printf("d: ");
	// print_vec(d);
    det = dot_product(&e[0], &d); // det = e1 · d

	// Check if the ray is parallel to the triangle
	//printf("det ?%f\n\t", det);
	if (det < 1e-6 && det > -1e-6)
		return;
	//printf("det: %f\n", det);

	// Calculate u parameter
	//printf("cal_parameter ?\n\t");
	u = dot_product(&p, &d) / det;
	if (u < 0 || u > 1)
		return ;
	//printf("cal_parameter: %f\n", u);

	// Calculate v parameter
	//printf("cal_parameter_v ?\n\t");
	cross_product(&p, &e[0], &q); // q = p × e1
	v = dot_product(&ray->dir, &q) / det;
	if (v < 1e-6 || u + v > 1)
		return ;
	//printf("cal_parameter_v: %f\n", v);

	// Calculate t parameter
	//printf("cal_parameter_t ?\n\t");
	t = dot_product(&e[1], &q) / det;
	if (t < 1e-6)
		return ;
	//printf("cal_parameter_t: %f\n", t);
	// Set the intersection details
	set_ts(t, ray, face, &q);
}
