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

	new.bottom[0] = (t_vec){
		.x = fmin(fmin(first->bottom[0].x, first->bottom[3].x), fmin(second->bottom[0].x, second->bottom[3].x)),
		.y = fmin(fmin(first->bottom[0].y, first->bottom[3].y), fmin(second->bottom[0].y, second->bottom[3].y)),
		.z = fmin(fmin(first->bottom[0].z, first->bottom[3].z), fmin(second->bottom[0].z, second->bottom[3].z)),
	};
	new.top[3] = (t_vec){
		.x = fmax(fmax(first->top[0].x, first->top[3].x), fmax(second->top[0].x, second->top[3].x)),
		.y = fmax(fmax(first->top[0].y, first->top[3].y), fmax(second->top[0].y, second->top[3].y)),
		.z = fmax(fmax(first->top[0].z, first->top[3].z), fmax(second->top[0].z, second->top[3].z)),
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
	t_hitbox		*new;
	const t_coord	end = scalar_multiplication_no_v(&cyl->coord, cyl->mag);
	
	new = create_bvh_node(NULL, NULL);
	if (!new)
		return (NULL);
	new->box = create_box(
		(t_vec){
			cyl->coord.x - cyl->radius,
			cyl->coord.y - cyl->radius,
			cyl->coord.z - cyl->radius
		},
		(t_vec){
			end.x + cyl->radius,
			end.y + cyl->radius,
			end.z + cyl->radius
		}
	);
	new->shape = (void *)cyl;
	new->type = CYLINDER;
	new->node_type = LEAF;
	return (new);
}

t_hitbox	*create_bhv(t_all *all, int start, int end, int depth)
{
	const int	mid = (start + end) / 2;
	t_hitbox	*left;
	t_hitbox	*right;
	t_hitbox	*parent;

	if (start > end)
		return (NULL);
	if (start == end)
	{
		if (all->shapes[start].type == SPHERE)
			return (box_around_sphere((t_sphere *)all->shapes[start].shape));
		else if (all->shapes[start].type == BOX)
			return (box_around_box(all->shapes[start].shape));
		else if (all->shapes[start].type == CYLINDER)
			return (box_around_cylinder(all->shapes[start].shape));
	}
	left = create_bhv(all, start, mid, depth + 1);
	left->depth = depth;
	right = create_bhv(all, mid + 1, end, depth + 1);
	right->depth = depth;
	parent = create_bvh_node(left, right);
	if (!parent)
		return (NULL);
	parent->box = box_around_two_box(&left->box, &right->box);
	parent->depth = depth;
	return (parent);
}
