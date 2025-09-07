/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 02:44:45 by hermesrolle       #+#    #+#             */
/*   Updated: 2025/09/07 02:47:54 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"
#include "tri_colors.h"

void	_draw_render_to_render(t_render *top, t_render *base)
{
	unsigned int	render_size;
	unsigned int	i;

	render_size = base->_size;
	i = 0;
	while (i < render_size)
	{
		(base->_data)[i] = _mix_colors_render_to_render(
				unsigned_to_argb((top->_data)[i]),
				unsigned_to_argb((base->_data)[i]));
		++i;
	}
}

// void	_draw_window(t_win *win)
// {
// 	t_tri_lib	*lib;
// 	t_render	*cursor;

// 	cursor = win->_renders;
// 	if (!cursor)
// 		return ;
// 	lib = tri_lib();
// 	mlx_put_image_to_window(lib->_mlx, win->_win, win->_renders->_img, 0, 0);
// 	while (cursor->_next)
// 	{
// 		mlx_put_image_to_window(lib->_mlx,
			// win->_win, cursor->_next->_img, 0, 0);
// 		// _draw_render_to_render(cursor->_next, win->_renders);
// 		cursor = cursor->_next;
// 	}
// 	printf("Background color : %x\n", _get_pixel(cursor, 0, 0));
// 	//_erase_fill_render(win->_renders, lib->_bg_color);
// }

void	_draw_window(t_win *win)
{
	t_tri_lib	*lib;
	t_render	*cursor;

	lib = tri_lib();
	cursor = win->_renders;
	while (cursor)
	{
		_draw_render_to_render(cursor, &win->_base_render._render);
		cursor = cursor->_next;
	}
	win->fps = _get_fps(&win->last_draw);
	printf("\rfps: %.2lf                   ", win->fps);
	mlx_put_image_to_window(lib->_mlx, win->_win,
		win->_base_render._img._img, 0, 0);
}

//_erase_fill_render(win->_renders, lib->_bg_color);

void	_draw_windows(void)
{
	t_win	*windows;

	windows = tri_lib()->_windows;
	while (windows)
	{
		_draw_window(windows);
		windows = windows->_next;
	}
}
