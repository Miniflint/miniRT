/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 03:38:27 by hermesrolle       #+#    #+#             */
/*   Updated: 2025/08/16 01:46:43 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"

t_img	*_open_img(char *path)
{
	(void)path;
	return (malloc(sizeof(t_img)));
}

// void	_close_window_hook(t_tri_lib *lib)
// {
// 	t_win	*windows;

// 	windows = lib->_windows;
// 	while (windows)
// 	{
// 		mlx_hook(windows->_win, 17, 0, _close_window, windows);
// 		windows = windows->_next;
// 	}
// }

// void	delay(int fps)
// {
// 	usleep(1000000 / fps);
// }

void	_refresh_window(t_win *win)
{
	if (!win || !win->_win || !win->_renders)
	{
		tri_lib()->_ernum = TRI_INVALID_VALUE;
		return ;
	}
}

t_tri_lib	*tri_lib(void)
{
	static t_tri_lib	tri_lib = {
		.init = _init_tri_lib, .destroy = _destroy_tri_lib,
		.loop = _main_loop, .delay = _delay, .get_end_function = _get_end_func,
		.create_window = _create_window, .create_render = _create_render,
		.destroy_window = _destroy_window, .destroy_render = _destroy_render,
		.print_error = _print_error, .get_error_msg = _get_error_message,
		.open_img = _open_img, .get_pixel = _get_pixel,
		.put_pixel_to_render = _put_pixel_to_render, .quit = _quit,
		.replace_pixel_on_render = _replace_pixel_on_render,
		.put_pixel_to_window = _put_pixel_to_window,
		.replace_pixel_on_window = _replace_pixel_on_window,
		.erase_fill_render = _erase_fill_render, .fill_render = _fill_render,
		.erase_render = _erase_render, .erase_window = _erase_window,
		.erase_windows = _erase_windows, .draw_window = _draw_window,
		.draw_windows = _draw_windows, .change_background = _change_background,
		._imgs = NULL, ._windows = NULL, ._mlx = NULL, .event = NULL,
		._user_content = NULL, ._bg_color = BACKGROUND_COLOR,
		._ernum = TRI_SUCCESS, ._user_end = NULL,
		._error_msg = {"TRI Error : succes\n", "TRI Error : failure\n",
		"TRI Error : tri_lib unitialised\n", "TRI Exit : succes\n",
		"TRI Error : malloc failure\n", "TRI Error : create window failure\n",
		"TRI Error : create render failure\n", "TRI Error : invalid value\n",
		"TRI Error : initialisation failure\n", "TRI Error : undefined\n"}};

	return (&tri_lib);
}
