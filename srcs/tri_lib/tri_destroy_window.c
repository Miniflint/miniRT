/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_destroy_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herolle <herolle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:31:44 by herolle           #+#    #+#             */
/*   Updated: 2025/06/19 16:35:03 by herolle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"

static void	_destroy_window_node(t_tri_lib *lib, t_win *win)
{
	if (lib->event && lib->event->win_id == win)
		lib->event = NULL;
	mlx_destroy_window(lib->_mlx, win->_win);
	win->_win = NULL;
	if (win->_renders)
		_free_renders(win->_renders);
	_destroy_base_render(&win->_base_render);
	free(win);
	win = NULL;
}

void	_destroy_window(t_win *win)
{
	t_tri_lib	*lib;
	t_win		*cursor;
	t_win		*tmp;

	if (!win)
		return ;
	lib = tri_lib();
	cursor = lib->_windows;
	printf("%p - %p\n", win, cursor);
	if (cursor == win)
	{
		lib->_windows = lib->_windows->_next;
		return (_destroy_window_node(lib, cursor));
	}
	while (cursor->_next && cursor->_next != win)
		cursor = cursor->_next;
	if (!cursor->_next)
		return ;
	tmp = cursor->_next;
	cursor->_next = tmp->_next;
	_destroy_window_node(lib, tmp);
}
