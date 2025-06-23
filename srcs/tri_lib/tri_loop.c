/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herolle <herolle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:28:01 by herolle           #+#    #+#             */
/*   Updated: 2025/06/23 13:16:07 by herolle          ###   ########.fr       */
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
		mlx_hook(cursor_win->_win, MLX_KEY_PRESS_HOOK, (1L<<0), _get_key_press, cursor_win);
		mlx_hook(cursor_win->_win, MLX_KEY_RELEASE_HOOK, (1L<<1), _get_key_release, cursor_win);
		cursor_win = cursor_win->_next;
	}
	mlx_loop_hook(lib->_mlx, _loop_event, lib);
	_close_window_hook(lib);
	mlx_loop(lib->_mlx);
	return (TRI_SUCCESS);
}
