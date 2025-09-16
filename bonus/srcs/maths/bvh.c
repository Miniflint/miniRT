#include "miniRT.h"

t_hitbox	*create_bvh_node(t_hitbox *l, t_hitbox *r)
{
	t_hitbox	*new;

	new = malloc(sizeof(t_hitbox));
	if (!new)
		return (NULL);
	new->left = l;
	new->right = r;
	new->shape = NULL;
	new->type = HITBOX;
	new->node_type = INTERNAL;
	return (new);
}

t_bvh	box_around_two_box(t_bvh *first, t_bvh *second)
{
	t_bvh	new;

	if (!second)
		return (create_box(first->bottom[0], first->top[3]));
	new.bottom[0] = (t_vec){
		.x = fmin(fmin(first->bottom[0].x, first->bottom[3].x),
			fmin(second->bottom[0].x, second->bottom[3].x)),
		.y = fmin(fmin(first->bottom[0].y, first->bottom[3].y),
			fmin(second->bottom[0].y, second->bottom[3].y)),
		.z = fmin(fmin(first->bottom[0].z, first->bottom[3].z),
			fmin(second->bottom[0].z, second->bottom[3].z)),
	};
	new.top[3] = (t_vec){
		.x = fmax(fmax(first->top[0].x, first->top[3].x),
			fmax(second->top[0].x, second->top[3].x)),
		.y = fmax(fmax(first->top[0].y, first->top[3].y),
			fmax(second->top[0].y, second->top[3].y)),
		.z = fmax(fmax(first->top[0].z, first->top[3].z),
			fmax(second->top[0].z, second->top[3].z)),
	};
	return (create_box(new.bottom[0], new.top[3]));
}

t_hitbox	*box_around_sphere(t_sphere *sphere)
{
	t_hitbox	*new;

	new = create_bvh_node(NULL, NULL);
	if (!new)
		return (NULL);
	new->box = create_box(
			(t_vec){
			sphere->coord.x - sphere->radius,
			sphere->coord.y - sphere->radius,
			sphere->coord.z - sphere->radius
		},
			(t_vec){
			sphere->coord.x + sphere->radius,
			sphere->coord.y + sphere->radius,
			sphere->coord.z + sphere->radius
		}
			);
	new->shape = (void *)sphere;
	new->type = SPHERE;
	new->node_type = LEAF;
	return (new);
}

t_hitbox	*box_around_box(t_box *box)
{
	t_hitbox	*new;

	new = create_bvh_node(NULL, NULL);
	if (!new)
		return (NULL);
	new->box = create_box(box->box.bottom[0], box->box.top[3]);
	new->shape = (void *)box;
	new->type = BOX;
	new->node_type = LEAF;
	return (new);
}

t_hitbox	*box_around_cylinder(t_cylinder *cyl)
{
	t_hitbox	*new;
	t_coord		end;

	new = create_bvh_node(NULL, NULL);
	if (!new)
		return (NULL);
	end = scalar_multiplication_no_v(&cyl->vec, cyl->height);
	end.x += cyl->coord.x;
	end.y += cyl->coord.y;
	end.z += cyl->coord.z;
	new->box = create_box(
			(t_vec){fmin(cyl->coord.x, end.x) - cyl->radius,
			fmin(cyl->coord.y, end.y) - cyl->radius,
			fmin(cyl->coord.z, end.z) - cyl->radius},
			(t_vec){fmax(cyl->coord.x, end.x) + cyl->radius,
			fmax(cyl->coord.y, end.y) + cyl->radius,
			fmax(cyl->coord.z, end.z) + cyl->radius}
			);
	new->shape = (void *)cyl;
	new->type = CYLINDER;
	new->node_type = LEAF;
	return (new);
}

static int	queue_helper(t_queue *q, int depth)
{
	t_hitbox	*l;
	t_hitbox	*r;
	t_hitbox	*dad;

	while (queue_size(q) > 1)
	{
		l = queue_pop(q);
		r = NULL;
		if (!queue_is_empty(q))
			r = queue_pop(q);
		dad = create_bvh_node(l, r);
		if (!dad)
			return (1);
		dad->box = box_around_two_box(&l->box, &r->box);
		l->depth = depth;
		r->depth = depth;
		queue_push(q, dad);
		dad->depth = depth;
	}
	return (0);
}

static t_hitbox	*queue_helper_2(t_all *all, t_queue *q, int i)
{
	t_hitbox	*dad;

	dad = NULL;
	if (all->shapes[i].type == SPHERE)
		dad = box_around_sphere(all->shapes[i].shape);
	else if (all->shapes[i].type == BOX)
		dad = box_around_box(all->shapes[i].shape);
	else if (all->shapes[i].type == CYLINDER)
		dad = box_around_cylinder(all->shapes[i].shape);
	else if (all->shapes[i].type == OBJECT)
		dad = create_bvh_triangles(all->shapes[i].shape);
	if (!dad)
	{
		while (i && --i)
			free(q->nodes[i]);
		return (queue_free(q));
	}
	return (dad);
}

t_hitbox	*create_bvh_iter(t_all *all, int end, int depth)
{
	t_queue		q;
	t_hitbox	*dad;
	int			i;

	if (queue_init(&q, end))
		return (NULL);
	dad = NULL;
	i = -1;
	while (++i < end)
	{
		dad = queue_helper_2(all, &q, i);
		queue_push(&q, dad);
	}
	if (queue_helper(&q, depth))
		return (NULL);
	dad = queue_pop(&q);
	queue_free(&q);
	if (dad->node_type == INTERNAL)
	{
		dad->node_type = ROOT;
		dad->type = HITBOX;
	}
	return (dad);
}
