/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_put_pixel_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 03:59:18 by hermesrolle       #+#    #+#             */
/*   Updated: 2025/08/29 11:40:20 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

unsigned int	_get_pixel(t_render *render, int x, int y)
{
	if (x < 0 || y < 0 || x >= render->_width
		|| y >= render->_height)
		return (tri_lib()->_bg_color);
	return ((render->_data)[(y * render->_width) + x]);
	return (0);
}

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

void	_replace_sized_pixel_on_render(t_render *render,
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
	fflush(stdout); //not permited
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

void	_change_background(unsigned int color)
{
	tri_lib()->_bg_color = color & 0xFFFFFF;
}
