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
	t_hitbox	*new;
	t_coord		end;

	new = create_bvh_node(NULL, NULL);
	if (!new)
		return (NULL);
	end = scalar_multiplication_no_v(&cyl->vec, cyl->height);
	new->box = create_box(
		(t_vec){
			fmin(cyl->coord.x, end.x) - cyl->radius,
			fmin(cyl->coord.y, end.y) - cyl->radius,
			fmin(cyl->coord.z, end.z) - cyl->radius
		},
		(t_vec){
			fmax(cyl->coord.x, end.x) + cyl->radius,
			fmax(cyl->coord.y, end.y) + cyl->radius,
			fmax(cyl->coord.z, end.z) + cyl->radius
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
			return (box_around_sphere(all->shapes[start].shape));
		else if (all->shapes[start].type == BOX)
			return (box_around_box(all->shapes[start].shape));
		else if (all->shapes[start].type == CYLINDER)
			return (box_around_cylinder(all->shapes[start].shape));
		//else if (all->shapes[start].type == OBJECT)
		//	return (create_bvh_triangles(all->shapes[start].shape));
	}
	left = create_bhv(all, start, mid, depth + 1);
	right = create_bhv(all, mid + 1, end, depth + 1);
	parent = create_bvh_node(left, right);
	if (!parent)
		return (NULL);
	right->depth = depth;
	left->depth = depth;
	parent->box = box_around_two_box(&left->box, &right->box);
	parent->depth = depth;
	return (parent);
}
