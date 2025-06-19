#include "tri_lib.h"

t_tri_lib	*_init_tri_lib(void)
{
	t_tri_lib			*lib;

	lib = tri_lib();
	if (!lib->_mlx)
	{
		lib->_mlx = mlx_init();
		if (!lib->_mlx)
		{
			lib->_ernum = TRI_INIT_FAILURE;
			return (NULL);
		}
	}
	return (lib);
}