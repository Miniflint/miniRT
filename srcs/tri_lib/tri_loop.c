/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herolle <herolle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:28:01 by herolle           #+#    #+#             */
/*   Updated: 2025/08/29 12:44:42 by herolle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"
#include "tri_mlx_code.h"
#include <stdio.h>

void	_call_user_main(t_tri_lib *lib)
{
	double	fps;

	if (lib->fps_max < TRI_INF_FPS)
		while (!_get_tick_fps(lib, &lib->last_loop, &lib->fps))
			;
	else
		lib->fps = _get_fps(&lib->last_loop);
	if (lib->fps <= 0)
		fps = 0.01;
	else
		fps = lib->fps;
	lib->fps_delta = lib->fps_target / fps;
	if (lib->fps_delta < 0.05)
		lib->fps_delta = 0.05;
	else if (lib->fps_delta > 4.0)
		lib->fps_delta = 4;
	lib->_user_main(lib, lib->_user_content);
	_auto_draw(lib);
}

static int	_loop_event(t_tri_lib *lib)
{
	lib->event = NULL;
	_call_user_main(lib);
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

void	_get_mlx_hook(t_win *cursor_win)
{
	mlx_hook(cursor_win->_win, MLX_KEY_PRESS_HOOK,
		(1L << 0), _get_key_press, cursor_win);
	mlx_hook(cursor_win->_win, MLX_KEY_RELEASE_HOOK,
		(1L << 1), _get_key_release, cursor_win);
	mlx_hook(cursor_win->_win, 17, 0, _close_window, cursor_win);
	mlx_hook(cursor_win->_win, MLX_MOUSE_PRESS_HOOK, 1L << 2,
		_get_mouse_press, cursor_win);
	mlx_hook(cursor_win->_win, MLX_MOUSE_RELEASE_HOOK, 1L << 3,
		_get_mouse_release, cursor_win);
	mlx_hook(cursor_win->_win, MLX_MOUSE_MOVE_HOOK, 1L << 6,
		_get_mouse_move, cursor_win);
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
		_get_mlx_hook(cursor_win);
		cursor_win = cursor_win->_next;
	}
	mlx_loop_hook(lib->_mlx, _loop_event, lib);
	mlx_loop(lib->_mlx);
	return (TRI_SUCCESS);
}
