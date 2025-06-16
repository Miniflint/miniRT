#include "miniRT.h"

t_all	*__get_all(void)
{
	static t_all	rtn_all;

	return (&rtn_all);
}
