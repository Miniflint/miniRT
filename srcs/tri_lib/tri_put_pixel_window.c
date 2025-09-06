#include "tri_lib.h"
#include "tri_colors.h"

void	_put_pixel_to_window(t_win *win, t_argb color, int x, int y)
{
	unsigned int	i;
	t_render		*render;

	if (x < 0 || y < 0 || x >= win->_width || y >= win->_height)
		return ;
	if (win->_last_render)
		render = win->_last_render;
	else
		render = &win->_base_render._render;
	i = (y * render->_width) + x;
	(render->_data)[i]
		= render->_mix_colors(color,
			unsigned_to_argb((render->_data)[i]));
}

void	_replace_pixel_on_window(t_win *win, unsigned int color, int x, int y)
{
	t_render		*render;

	if (x < 0 || y < 0 || x >= win->_width || y >= win->_height)
		return ;
	if (win->_last_render)
	{
		render = win->_last_render;
		(render->_data)[(y * render->_width) + x] = color;
	}
	else
	{
		render = &win->_base_render._render;
		(render->_data)[(y * render->_width) + x]
			= render->_mix_colors(unsigned_to_argb(color),
				unsigned_to_argb(tri_lib()->_bg_color));
	}
}
