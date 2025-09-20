#include "miniRT.h"
#include "miniRT.h"

int	stack_init(t_stack *s)
{
	s->front = 0;
	s->capacity = 64;
	return (0);
}

int	stack_is_empty(t_stack *s)
{
	return (s->front == 0);
}

int	stack_size(t_stack *s)
{
	return (s->front);
}

int	stack_push(t_stack *s, t_hitbox *curr)
{
	if (s->front == s->capacity)
		return (1);
	s->nodes[s->front] = curr;
	s->front += 1;
	return (0);
}

t_hitbox	*stack_pop(t_stack *s)
{
	t_hitbox		*node;

	if (stack_is_empty(s))
		return (NULL);
	s->front -= 1;
	node = s->nodes[s->front];
	return (node);
}

t_hitbox	*stack_free(t_stack *s)
{
    (void)s;
	return (NULL);
}
