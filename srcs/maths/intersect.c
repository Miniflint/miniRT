/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:06:39 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:07:01 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	set_ts(double t, t_ray *ray, t_sphere *sphere)
{
	if (t >= 1e-6 && (isinf(ray->shape.t1) || t < ray->shape.t1))
	{
		ray->shape.t1 = t;
		ray->shape.shape = sphere;
		ray->shape.type = SPHERE;
		return ;
	}
}

void	intersect_ray_sphere(t_ray *ray, t_sphere *sphere)
{
	double			disciminant;
	double			t;
	const t_vec		co = sub_vectors_no_v(&ray->start, &sphere->coord);
	const double	b = 2 * dot_product((t_vec *)&co, &ray->dir);
	const double	c
		= dot_product((t_vec *)&co, (t_vec *)&co) - sphere->radius_squared;

	disciminant = b * b - 4.0 * c;
	if (disciminant < 0)
		return ;
	disciminant = sqrt(disciminant);
	t = (-b - disciminant) / 2;
	set_ts(t, ray, sphere);
	t = (-b + disciminant) / 2;
	set_ts(t, ray, sphere);
}
