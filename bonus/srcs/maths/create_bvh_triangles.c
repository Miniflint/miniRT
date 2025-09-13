#include "miniRT.h"

double lowest_2(double a, double b)
{
	const int a_nz = a != 0.0;
	const int b_nz = b != 0.0;
	const double both_nonzero = (double)(a_nz & b_nz);
	const double only_a = (double)(a_nz & !b_nz);
	const double only_b = (double)((!a_nz) & b_nz);

	return (both_nonzero * (a + (b - a) * (b < a)) + only_a * a + only_b * b);
}

double	lowest_3(double a, double b, double c)
{
	return (lowest_2(lowest_2(a, b), c));
}

double highest_2(double a, double b)
{
	const int a_nz = a != 0.0;
	const int b_nz = b != 0.0;
	const double both_nonzero = (double)(a_nz & b_nz);
	const double only_a = (double)(a_nz & !b_nz);
	const double only_b = (double)((!a_nz) & b_nz);

	return (both_nonzero * (a + (b - a) * (b > a)) + only_a * a + only_b * b);
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

t_hitbox	*iterative_triangles(t_face *faces, unsigned long end, int depth)
{
	unsigned long	i;
	t_queue			q;
	t_hitbox		*leaf;
	t_hitbox		*right;
	t_hitbox		*dad;

	if (queue_init(&q, end))
		return (NULL);
	i = -1;
	while (++i < end)
	{
		if (faces[i].is_wrong == 0)
		{
			leaf = box_around_triangle(&faces[i]);
		}
		if (!leaf)
		{
			while (i && --i)
				free(q.nodes[i]);
			return (queue_free(&q));
		}
		queue_push(&q, leaf);
	}
	while (queue_size(&q) > 1)
	{
		leaf = queue_pop(&q);
		right = NULL;
		if (!queue_is_empty(&q))
			right = queue_pop(&q);
		dad = create_bvh_node(leaf, right);
		if (!dad)
			return (NULL);
		dad->box = box_around_two_box(&leaf->box, &right->box);
		dad->depth = depth;
		queue_push(&q, dad);
		depth += 1;
	}
	dad = queue_pop(&q);
	queue_free(&q);
	dad->node_type = ROOT;
	return (dad);
}

t_hitbox	*create_bvh_triangles(t_object *obj)
{
	return (iterative_triangles(obj->faces, obj->nb_faces, 0));
}