#include "miniRT.h"

void	*create_empty_node(size_t size)
{
	void	*new_struct;

	new_struct = malloc(size);
	if (!new_struct)
		return (NULL);
	ft_memset(new_struct, 0, size);
	return (new_struct);
}
