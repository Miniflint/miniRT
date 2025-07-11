/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_create_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:11:42 by herolle           #+#    #+#             */
/*   Updated: 2025/06/20 18:09:10 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"

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
	win->_width = width;
	win->_height = height;
	win->_name = name;
	win->_renders = NULL;
	win->_last_render = NULL;
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
	return (win);
}
