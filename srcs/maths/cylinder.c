/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:06:37 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:07:03 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	set_ts(double t, t_ray *ray, t_cylinder *cylinder)
{
	t_vec	p;
	double	mag;

	if (t >= 1e-6 && (isinf(ray->shape.t1) || t < ray->shape.t1))
	{
		add_vectors(&ray->start, scalar_multiplication(&ray->dir, t, &p), &p);
		p = sub_vectors_no_v(&p, &cylinder->coord);
		mag = dot_product(&p, &cylinder->vec);
		if (mag < 0 || mag > cylinder->height || isnan(mag) || isinf(mag))
			return (0);
		cylinder->p = p;
		cylinder->mag = mag;
		ray->shape.t1 = t;
		ray->shape.shape = cylinder;
		ray->shape.type = CYLINDER;
		return (1);
	}
	return (0);
}

void	intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_vec	co;
	t_vec	tmp;
	t_vec	d;
	t_quad	q;

	co = sub_vectors_no_v(&ray->start, &cylinder->coord);
	tmp = scalar_multiplication_no_v(&cylinder->vec,
			dot_product(&co, &cylinder->vec));
	co = sub_vectors_no_v(&co, &tmp);
	tmp = scalar_multiplication_no_v(&cylinder->vec,
			dot_product(&ray->dir, &cylinder->vec));
	d = sub_vectors_no_v(&ray->dir, &tmp);
	q.a = dot_product(&d, &d);
	q.b = 2 * dot_product(&d, &co);
	q.c = dot_product(&co, &co) - cylinder->radius_squared;
	q.discriminant = q.b * q.b - (4 * q.a * q.c);
	if (q.discriminant < 0)
		return ;
	q.b = -q.b;
	q.a = 2 * q.a;
	q.discriminant = sqrt(q.discriminant);
	q.t = (q.b - q.discriminant) / q.a;
	set_ts(q.t, ray, cylinder);
	q.t = (q.b + q.discriminant) / q.a;
	set_ts(q.t, ray, cylinder);
}

void	closest_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	while (cylinder)
	{
		intersect_cylinder(ray, cylinder);
		cylinder = cylinder->next;
	}
}
