#include "miniRT.h"

int	get_vertex(t_vertex *vertex, char **s)
{
	vertex->x = ft_atof(s);
	if (ft_iswhitespace(*(++(*s))))
		return (printf(ERROR_X_DECODE, *((*s) - 1), *((*s) - 1)), 1);
	if (skip_till_number(s, 0))
		return (3);
	vertex->y = ft_atof(s);
	if (ft_iswhitespace(*(++(*s))))
		return (printf(ERROR_Y_DECODE, *((*s) - 1), *((*s) - 1)), 1);
	if (skip_till_number(s, 0))
		return (3);
	vertex->z = ft_atof(s);
	if (**s && !ft_iswhitespace(**s))
		return (printf(ERROR_Z_DECODE, **s, **s), 1);
	return (0);
}
