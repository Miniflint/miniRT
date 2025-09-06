#include "miniRT.h"

t_all	*__get_all(void)
{
	static t_all	rtn_all;

	return (&rtn_all);
}

t_object	*__get_head(t_object *curr_head)
{
	static t_object	*curr;

	if (curr_head)
		curr = curr_head;
	return (curr);
}
