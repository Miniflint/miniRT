#include "miniRT.h"

int	free_hitboxes(t_hitbox *root, unsigned long capacity)
{
	t_queue			q;
	t_hitbox		*curr;

	if (queue_init(&q, capacity))
		return (1);
	queue_push(&q, root);
	while (!queue_is_empty(&q))
	{
		curr = queue_pop(&q);
		if (!curr)
			continue ;
		queue_push(&q, curr->left);
		queue_push(&q, curr->right);
		free(curr);
	}
	queue_free(&q);
	return (0);
}
