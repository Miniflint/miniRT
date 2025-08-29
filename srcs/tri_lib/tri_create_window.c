/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_create_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:11:42 by herolle           #+#    #+#             */
/*   Updated: 2025/08/29 11:42:16 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"

static void	_set_win_value(t_win *win, char *name, int width, int height)
{
	win->_width = width;
	win->_height = height;
	win->_name = name;
	win->_renders = NULL;
	win->_last_render = NULL;
	win->fps = 0.0;
	win->auto_draw = 0;
}

t_win	*_create_window(char *name, int width, int height)
{
	t_win		*win;
	t_tri_lib	*lib;

	lib = tri_lib();
	if (width < 1 || height < 1 || !name)
		return (_set_ernum(lib, TRI_INVALID_VALUE));
	win = malloc(sizeof(t_win));
	if (!win)
		return (_set_ernum(lib, TRI_MALLOC_FAILURE));
	_set_win_value(win, name, width, height);
	win->_win = mlx_new_window(lib->_mlx, width, height, name);
	if (!win->_win)
		return (free(win), _set_ernum(lib, TRI_CREATE_WINDOW_FAILURE));
	if (_create_base_render(win) != TRI_SUCCESS)
		return (lib->print_error(lib->_ernum),
			mlx_destroy_window(lib->_mlx, win->_win), free(win), NULL);
	win->_next = lib->_windows;
	lib->_windows = win;
	_init_event(&win->event, win);
	lib->event = &win->event;
	gettimeofday(&win->last_draw, NULL);
	return (win);
}
