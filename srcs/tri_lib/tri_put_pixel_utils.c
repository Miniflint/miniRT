/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_put_pixel_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 03:59:18 by hermesrolle       #+#    #+#             */
/*   Updated: 2025/09/07 02:46:01 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"
#include "tri_colors.h"

unsigned int	_get_pixel(t_render *render, int x, int y)
{
	if (x < 0 || y < 0 || x >= render->_width
		|| y >= render->_height)
		return (tri_lib()->_bg_color);
	return ((render->_data)[(y * render->_width) + x]);
	return (0);
}

void	_erase_window(t_win *win)
{
	t_tri_lib	*lib;
	t_render	*cursor;

	lib = tri_lib();
	cursor = win->_renders;
	_erase_fill_render(&win->_base_render._render, lib->_bg_color);
	while (cursor)
	{
		_erase_render(cursor);
		cursor = cursor->_next;
	}
}

void	_erase_windows(void)
{
	t_win		*win;

	win = tri_lib()->_windows;
	while (win)
	{
		_erase_window(win);
		win = win->_next;
	}
}

void	_change_background(unsigned int color)
{
	tri_lib()->_bg_color = color & 0xFFFFFF;
}
