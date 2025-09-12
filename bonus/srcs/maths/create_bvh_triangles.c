#include "miniRT.h"

double	lowest_2(double a, double b)
{
	return a + (b - a) * (b < a);
}

double	lowest_3(double a, double b, double c)
{
	return (lowest_2(lowest_2(a, b), c));
}

double	highest_2(double a, double b)
{
	return a + (b - a) * (b < a);
}

double	highest_3(double a, double b, double c)
{
	return (highest_2(highest_2(a, b), c));
}

t_hitbox	*box_around_triangle(t_face *face)
{
	t_hitbox	*new;
	double		lowest[3];
	double		highest[3];

	lowest[0] = lowest_3(face->vertices[0]->x, face->vertices[1]->x, face->vertices[2]->x);
	lowest[1] = lowest_3(face->vertices[0]->y, face->vertices[1]->y, face->vertices[2]->y);
	lowest[2] = lowest_3(face->vertices[0]->z, face->vertices[1]->z, face->vertices[2]->z);
	highest[0] = highest_3(face->vertices[0]->x, face->vertices[1]->x, face->vertices[2]->x);
	highest[1] = highest_3(face->vertices[0]->y, face->vertices[1]->y, face->vertices[2]->y);
	highest[2] = highest_3(face->vertices[0]->z, face->vertices[1]->z, face->vertices[2]->z);
	if (face->vertices[3])
	{
		lowest[0] = lowest_2(lowest[0], face->vertices[3]->x);
		lowest[1] = lowest_2(lowest[1], face->vertices[3]->y);
		lowest[2] = lowest_2(lowest[2], face->vertices[3]->z);
		highest[0] = highest_2(highest[0], face->vertices[3]->x);
		highest[1] = highest_2(highest[1], face->vertices[3]->y);
		highest[2] = highest_2(highest[2], face->vertices[3]->z);
	}

	new = create_bvh_node(NULL, NULL);
	if (!new)
		return (NULL);
	new->box = create_box(
		(t_vec){
			lowest[0],
			lowest[1],
			lowest[2]
		},
		(t_vec){
			highest[0],
			highest[1],
			highest[2]
	});
	new->shape = (void *)face;
	new->type = TRIANGLE;
	new->node_type = LEAF;
	return (new);
}

t_hitbox	*recursive_triangles(t_object *obj,
	unsigned long start, unsigned long end, unsigned long depth)
{
	t_hitbox	*left;
	t_hitbox	*right;
	t_hitbox	*dad;

	const unsigned int	mid = end / 2;
	if (start > end)
		return (NULL);
	if (start == end)
	{
		if (!obj->faces[start].is_wrong)
			return (NULL);
		return (box_around_triangle(&obj->faces[start]));
	}
	left = recursive_triangles(obj, start, mid, depth + 1);
	right = recursive_triangles(obj, mid + 1, end, depth + 1);
	dad = create_bvh_node(left, right);
	if (!dad)
		return (NULL);
	dad->type = HITBOX;
	dad->node_type = INTERNAL;
	left->depth = depth;
	right->depth = depth;
	dad->box = box_around_two_box(&left->box, &right->box);
	dad->depth = depth;
	return (dad);
}

t_hitbox	*create_bvh_triangles(t_object *obj)
{
	return (recursive_triangles(obj, 0, obj->nb_vertices, 0));
}