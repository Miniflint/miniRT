#include "tri_lib.h"
#include "tri_colors.h"

void	_auto_draw(t_tri_lib *lib)
{
	t_win	*wins;

	if (!lib->auto_draw)
		return ;
	wins = lib->_windows;
	while (wins)
	{
		if (wins->auto_draw)
			_draw_window(wins);
		wins = wins->_next;
	}
}
