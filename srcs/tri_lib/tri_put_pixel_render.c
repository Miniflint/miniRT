#include "tri_lib.h"
#include "tri_colors.h"

void	_put_pixel_to_render(t_render *render, t_argb color, int x, int y)
{
	unsigned int	i;

	if (x < 0 || y < 0 || x >= render->_width
		|| y >= render->_height)
		return ;
	i = (y * render->_width) + x;
	(render->_data)[i]
		= render->_mix_colors(color,
			unsigned_to_argb((render->_data)[i]));
}

void	_replace_pixel_on_render(t_render *render,
	unsigned int color, int x, int y)
{
	if (x < 0 || y < 0 || x >= render->_width
		|| y >= render->_height)
		return ;
	(render->_data)[(y * render->_width) + x] = color;
}

void	_replace_s_px_on_render(t_render *render,
	unsigned int color, t_point2d p, int size)
{
	int	i;
	int	j;

	if (p.x < 0 || p.y < 0)
		return ;
	i = 0;
	while (i + p.y < render->_height && i < size)
	{
		j = 0;
		while (j + p.x < render->_width && j < size)
			(render->_data)[((i + p.y) * render->_width) + (p.x + j++)] = color;
		++i;
	}
}
