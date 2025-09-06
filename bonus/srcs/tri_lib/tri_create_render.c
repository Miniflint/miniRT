/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_create_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:29:12 by herolle           #+#    #+#             */
/*   Updated: 2025/08/29 10:59:59 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"

static t_render	*_new_render(t_tri_lib *lib, t_win *win)
{
	t_render	*render;

	render = malloc(sizeof(t_render));
	if (!render)
		return (_set_ernum(lib, TRI_MALLOC_FAILURE));
	render->_size = win->_width * win->_height;
	render->_data = malloc(sizeof(unsigned int *) * render->_size);
	if (!render->_data)
		return (free(render), _set_ernum(lib, TRI_MALLOC_FAILURE));
	render->_mix_colors = mix_colors_normal_u;
	render->_width = win->_width;
	render->_height = win->_height;
	render->_parent_win = win;
	render->_next = NULL;
	return (render);
}

t_render	*_create_render(t_win *win)
{
	t_tri_lib	*lib;
	t_render	*tmp;

	lib = tri_lib();
	if (!win || !win->_win)
		return (_set_ernum(lib, TRI_INVALID_VALUE));
	tmp = _new_render(lib, win);
	if (!tmp)
		return (NULL);
	if (!win->_renders)
	{
		win->_renders = tmp;
		win->_last_render = win->_renders;
	}
	else
	{
		win->_last_render->_next = tmp;
		win->_last_render = win->_last_render->_next;
	}
	_erase_render(win->_last_render);
	return (tmp);
}

static void	init_render(t_win *win)
{
	win->_base_render._render._width = win->_base_render._img._size_line / 4;
	win->_base_render._render._height = win->_height;
	win->_base_render._render._size = win->_width * win->_height;
	win->_base_render._img._width = win->_base_render._render._width;
	win->_base_render._render._parent_win = win;
	win->_base_render._render._next = NULL;
	win->_base_render._render._data
		= (unsigned int *)win->_base_render._img._data;
	win->_base_render._render._mix_colors = mix_colors_normal_u_no_a;
}

int	_create_base_render(t_win *win)
{
	t_tri_lib	*lib;

	lib = tri_lib();
	if (!win || !win->_win)
	{
		_set_ernum(lib, TRI_INVALID_VALUE);
		return (TRI_INVALID_VALUE);
	}
	win->_base_render._img._img
		= mlx_new_image(lib->_mlx, win->_width, win->_height);
	if (!win->_base_render._img._img)
	{
		_set_ernum(lib, TRI_CREATE_RENDER_FAILURE);
		return (TRI_CREATE_RENDER_FAILURE);
	}
	win->_base_render._img._data
		= mlx_get_data_addr(
			win->_base_render._img._img, &win->_base_render._img._bpp,
			&win->_base_render._img._size_line,
			&win->_base_render._img._endian);
	init_render(win);
	_erase_fill_render(&win->_base_render._render, lib->_bg_color);
	return (TRI_SUCCESS);
}
