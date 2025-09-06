#include "tri_lib.h"
#include "tri_colors.h"

void	_erase_fill_render(t_render *render, unsigned int color)
{
	unsigned int	render_size;
	unsigned int	i;

	render_size = render->_size;
	i = 0;
	while (i < render_size)
		((unsigned int *)render->_data)[i++] = color;
}

void	_fill_render(t_render *render, t_argb color)
{
	unsigned int	render_size;
	unsigned int	i;

	render_size = render->_size;
	i = 0;
	while (i < render_size)
	{
		(render->_data)[i]
			= render->_mix_colors(color, unsigned_to_argb((render->_data)[i]));
		++i;
	}
}

void	_erase_render(t_render *render)
{
	unsigned int	render_size;
	unsigned int	i;

	render_size = render->_size;
	i = 0;
	while (i < render_size)
		((unsigned int *)render->_data)[i++] = 0;
}
