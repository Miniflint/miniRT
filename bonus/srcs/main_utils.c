#include "miniRT.h"

static void	if_queue_internal(t_queue *q, t_hitbox *curr, FILE *file)
{
	if (curr->node_type == INTERNAL)
		fprintf(file, "\t\"%p\" [label=\"%p\"];\n",
			(void *)curr, (void *)curr);
	else if (curr->node_type == ROOT)
		fprintf(file, "\t\"%p\" [label=\"%p\"];\n",
			(void *)curr, (void *)curr);
	if (curr->left)
	{
		fprintf(file, "\t\"%p\" -> \"%p\";\n",
			(void *)curr, (void *)curr->left);
		queue_push(q, curr->left);
	}
	if (curr->right)
	{
		fprintf(file, "\t\"%p\" -> \"%p\";\n",
			(void *)curr, (void *)curr->right);
		queue_push(q, curr->right);
	}
}

static void	if_queue_leaf(t_hitbox *curr, FILE *file)
{
	if (curr->type == SPHERE)
		fprintf(file, "\t\"%p\" [label=\"SPHERE\"];\n", (void *)curr);
	else if (curr->type == BOX)
		fprintf(file, "\t\"%p\" [label=\"BOX\"];\n", (void *)curr);
	else if (curr->type == CYLINDER)
		fprintf(file, "\t\"%p\" [label=\"CYLINDER\"];\n", (void *)curr);
	else if (curr->type == OBJECT)
		fprintf(file, "\t\"%p\" [label=\"OBJECT\"];\n", (void *)curr);
	else if (curr->type == TRIANGLE)
		fprintf(file, "\t\"%p\" [label=\"TRIANGLE\"];\n", (void *)curr);
}

void	print_bvh_dot_iter(t_hitbox *root, FILE *file)
{
	t_queue		q;
	t_hitbox	*curr;

	if (queue_init(&q,
			__get_all()->nb_shapes + get_depth_objs(__get_all()->objects)))
		return ;
	queue_push(&q, root);
	while (!queue_is_empty(&q))
	{
		curr = queue_pop(&q);
		if (!curr)
			continue ;
		if (curr->node_type == LEAF)
			if_queue_leaf(curr, file);
		else
			if_queue_internal(&q, curr, file);
	}
	queue_free(&q);
}

void	export_bvh_to_dot(t_hitbox *root)
{
	FILE	*f;

	f = fopen("out.dot", "w");
	fprintf(f, "digraph BVH {\n");
	print_bvh_dot_iter(root, f);
	fprintf(f, "}\n");
	fclose(f);
}
