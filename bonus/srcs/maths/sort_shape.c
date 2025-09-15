#include "miniRT.h"

void	swap_shapes(t_shape *arr, int i, int closest)
{
	t_shape	tmp;

	tmp = arr[i];
	arr[i] = arr[closest];
	arr[closest] = tmp;
}

void	sort_shape(t_shape *arr)
{
	int	i;
	int	j;
	int	closest;

	i = 0;
	while (arr[i].type != END_SHAPE)
	{
		j = i + 1;
		closest = j;
		while (arr[j].type != END_SHAPE)
		{
			if (arr[j].type != OBJECT)
				if (distance_formula(&arr[i].origin, &arr[j].origin)
					< distance_formula(&arr[i].origin, &arr[closest].origin))
					closest = j;
			j++;
		}
		if (closest != i + 1)
			swap_shapes(arr, i + 1, closest);
		i++;
	}
}
