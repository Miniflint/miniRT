#include "miniRT.h"


int	queue_init(t_queue *q, int capacity)
{
	const int	max_size = capacity * 2;
	q->nodes = malloc(sizeof(t_hitbox *) * (max_size));
	if (!q->nodes)
		return (1);
	q->front = 0;
	q->back = 0;
	q->capacity = max_size;
	return (0);
}

int	queue_is_empty(t_queue *q)
{
	return (q->front == q->back);
}

int	queue_size(t_queue *q)
{
	return (q->back - q->front + q->capacity) % q->capacity;
}

int	queue_push(t_queue *q, t_hitbox *curr)
{
	unsigned long	next_back;

	next_back = (q->back + 1) % q->capacity;
	q->nodes[q->back] = curr;
	if (next_back == q->front)
		return (1);
	q->back = next_back;
	return (0);
}

t_hitbox	*queue_pop(t_queue *q)
{
	t_hitbox		*node;
	unsigned long	tmp;

	if (queue_is_empty(q))
		return (NULL);
	node = q->nodes[q->front];
	tmp = (q->front + 1) % q->capacity;
	q->front = tmp;
	return (node);
}

t_hitbox	*queue_free(t_queue *q)
{
	if (q->nodes)
		free(q->nodes);
	return (NULL);
}

void	write_in_char(char str[100], const char *to_write)
{
	int	i;

	i = -1;
	while (to_write[++i])
		str[i] = to_write[i];
	str[i] = 0;
}

void	queue_print(t_queue queue)
{
	t_hitbox	*hitbox;
	char		str[100];

	while (!queue_is_empty(&queue))
	{
		hitbox = queue_pop(&queue);
		if (!hitbox)
			return ;
		if (hitbox->node_type == INTERNAL)
			write_in_char(str, "INTERNAL");
		else if (hitbox->node_type == LEAF)
		{
			if (hitbox->type == TRIANGLE)
				write_in_char(str, "LEAF: TRIANGLE");
			else if (hitbox->type == SPHERE)
				write_in_char(str, "LEAF: SPHERE");
			else if (hitbox->type == CYLINDER)
				write_in_char(str, "LEAF: CYLINDER");
			else if (hitbox->type == BOX)
				write_in_char(str, "LEAF: BOX");
		}
		else if (hitbox->node_type == ROOT)
			write_in_char(str, "INTERNAL");
		printf("|%d: %s |\n", queue_size(&queue),str);
	}
}