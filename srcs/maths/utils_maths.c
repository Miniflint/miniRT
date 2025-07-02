#include "miniRT.h"

int ft_mult(int x, int y)
{
	if ((y & (y - 1)) == 0)
		return (x << (y - 1));
	return (1);
}