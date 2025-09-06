/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_maths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:06:54 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:06:58 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	vec_magnitude(t_vec *a)
{
	return (sqrt((a->x * a->x) + (a->y * a->y) + (a->z * a->z)));
}

t_vec	*add_vectors(t_vec *a, t_vec *b, t_vec *c)
{
	c->x = a->x + b->x;
	c->y = a->y + b->y;
	c->z = a->z + b->z;
	return (c);
}

t_vec	*sub_vectors(t_vec *a, t_vec *b, t_vec *c)
{
	c->x = a->x - b->x;
	c->y = a->y - b->y;
	c->z = a->z - b->z;
	return (c);
}

t_vec	sub_vectors_no_v(t_vec *a, t_vec *b)
{
	return (
		(t_vec){
		.x = a->x - b->x,
		.y = a->y - b->y,
		.z = a->z - b->z
	}
	);
}

t_vec	*norm_vectors(t_vec *a, double magnitude, t_vec *c)
{
	c->x = a->x / magnitude;
	c->y = a->y / magnitude;
	c->z = a->z / magnitude;
	return (c);
}
