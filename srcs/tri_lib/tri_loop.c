/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:28:01 by herolle           #+#    #+#             */
/*   Updated: 2025/07/10 17:14:22 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"
#include "tri_mlx_code.h"
#include <stdio.h>

void	_delay(int fps)
{
	(void)fps;
	return ;
}

static int	_loop_event(t_tri_lib *lib)
{
	lib->event = NULL;
	lib->_user_main(lib, lib->_user_content);
	return (0);
}

static int	_close_window(t_win *win)
{
	t_tri_lib	*lib;

	lib = tri_lib();
	lib->destroy_window(win);
	if (!lib->_windows)
		lib->quit();
	return (1);
}

int	_main_loop(int (*f)(t_tri_lib *, void *), void *content)
{
	t_tri_lib	*lib;
	t_win		*cursor_win;

	lib = tri_lib();
	if (!lib->_mlx)
		return (TRI_UNITIALISED);
	lib->_user_main = f;
	lib->_user_content = content;
	cursor_win = lib->_windows;
	while (cursor_win && cursor_win->_win)
	{
		mlx_hook(cursor_win->_win, MLX_KEY_PRESS_HOOK, (1L << 0), _get_key_press, cursor_win);
		mlx_hook(cursor_win->_win, MLX_KEY_RELEASE_HOOK, (1L << 1), _get_key_release, cursor_win);
		mlx_hook(cursor_win->_win, 17, 0, _close_window, cursor_win);
		mlx_hook(cursor_win->_win, MLX_MOUSE_PRESS_HOOK, 1L << 2, _get_mouse_press, cursor_win);
		mlx_hook(cursor_win->_win, MLX_MOUSE_RELEASE_HOOK, 1L << 3, _get_mouse_release, cursor_win);
			mlx_hook(cursor_win->_win, MLX_MOUSE_MOVE_HOOK, 1L << 6, _get_mouse_move, cursor_win);
		cursor_win = cursor_win->_next;
	}
	mlx_loop_hook(lib->_mlx, _loop_event, lib);
	mlx_loop(lib->_mlx);
	return (TRI_SUCCESS);
}
