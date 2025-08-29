/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_get_key_event.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 03:34:21 by hermesrolle       #+#    #+#             */
/*   Updated: 2025/08/29 11:10:51 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"
#include "tri_mlx_code.h"

#ifdef __linux__

static void	_special_key_set(int keycode, char *key)
{
	if (keycode == MLX_KEY_UP)
		*key = KEY_UP;
	else if (keycode == MLX_KEY_DOWN)
		*key = KEY_DOWN;
	else if (keycode == MLX_KEY_LEFT)
		*key = KEY_LEFT;
	else if (keycode == MLX_KEY_RIGHT)
		*key = KEY_RIGHT;
	else if (keycode == MLX_KEY_CTRL)
		*key = KEY_CTRL;
	else if (keycode == MLX_KEY_SHIFT_LEFT)
		*key = KEY_SHIFT_LEFT;
	else if (keycode == MLX_KEY_SHIFT_RIGHT)
		*key = KEY_SHIFT_RIGHT;
	else if (keycode == MLX_KEY_ESC)
		*key = KEY_ESC;
	else
		*key = 0;
}

static unsigned char	_set_key(int keycode, t_win *win,
	t_event_type type, const unsigned char codes[MLX_MAX_CODE])
{
	unsigned char	key;

	win->event.type = type;
	if (keycode >= MLX_MAX_CODE)
		_special_key_set(keycode, &key);
	else
		key = codes[keycode];
	win->event.key_id = key;
	if (type == KEY_PRESS)
		win->event.key[key] = 1;
	else
		win->event.key[key] = 0;
	return (key);
}

static unsigned char	_get_key_event(int keycode, t_win *win,
	t_event_type type)
{
	static const unsigned char	codes[MLX_MAX_CODE] = {[MLX_KEY_A] = 'a',
	[MLX_KEY_B] = 'b', [MLX_KEY_C] = 'c', [MLX_KEY_D] = 'd', [MLX_KEY_E] = 'e',
	[MLX_KEY_F] = 'f', [MLX_KEY_G] = 'g', [MLX_KEY_H] = 'h', [MLX_KEY_I] = 'i',
	[MLX_KEY_J] = 'j', [MLX_KEY_K] = 'k', [MLX_KEY_L] = 'l', [MLX_KEY_M] = 'm',
	[MLX_KEY_N] = 'n', [MLX_KEY_O] = 'o', [MLX_KEY_P] = 'p', [MLX_KEY_Q] = 'q',
	[MLX_KEY_R] = 'r', [MLX_KEY_S] = 's', [MLX_KEY_T] = 't', [MLX_KEY_U] = 'u',
	[MLX_KEY_V] = 'v', [MLX_KEY_W] = 'w', [MLX_KEY_X] = 'x', [MLX_KEY_Y] = 'y',
	[MLX_KEY_Z] = 'z', [MLX_KEY_0] = '0', [MLX_KEY_1] = '1', [MLX_KEY_2] = '2',
	[MLX_KEY_3] = '3', [MLX_KEY_4] = '4', [MLX_KEY_5] = '5', [MLX_KEY_6] = '6',
	[MLX_KEY_7] = '7', [MLX_KEY_8] = '8', [MLX_KEY_9] = '9',
	[MLX_KEY_SPACE] = ' ', [MLX_KEY_ENTER] = '\n', [MLX_KEY_DEL] = KEY_DEL,
	[MLX_KEY_BACKSPACE] = KEY_BACKSPACE, [MLX_KEY_ALT_LEFT] = KEY_ALT_LEFT,
	[MLX_KEY_ALT_RIGHT] = KEY_ALT_RIGHT, [MLX_KEY_CMD_LEFT] = KEY_CMD_LEFT,
	[MLX_KEY_CMD_RIGHT] = KEY_CMD_RIGHT};

	return (_set_key(keycode, win, type, codes));
}

#else

static unsigned char	_get_key_event(int keycode, t_win *win,
	t_event_type type)
{
	static const unsigned char	codes[MLX_MAX_CODE] = {[MLX_KEY_A] = 'a',
	[MLX_KEY_B] = 'b', [MLX_KEY_C] = 'c', [MLX_KEY_D] = 'd', [MLX_KEY_E] = 'e',
	[MLX_KEY_F] = 'f', [MLX_KEY_G] = 'g', [MLX_KEY_H] = 'h', [MLX_KEY_I] = 'i',
	[MLX_KEY_J] = 'j', [MLX_KEY_K] = 'k', [MLX_KEY_L] = 'l', [MLX_KEY_M] = 'm',
	[MLX_KEY_N] = 'n', [MLX_KEY_O] = 'o', [MLX_KEY_P] = 'p', [MLX_KEY_Q] = 'q',
	[MLX_KEY_R] = 'r', [MLX_KEY_S] = 's', [MLX_KEY_T] = 't', [MLX_KEY_U] = 'u',
	[MLX_KEY_V] = 'v', [MLX_KEY_W] = 'w', [MLX_KEY_X] = 'x', [MLX_KEY_Y] = 'y',
	[MLX_KEY_Z] = 'z', [MLX_KEY_0] = '0', [MLX_KEY_1] = '1', [MLX_KEY_2] = '2',
	[MLX_KEY_3] = '3', [MLX_KEY_4] = '4', [MLX_KEY_5] = '5', [MLX_KEY_6] = '6',
	[MLX_KEY_7] = '7', [MLX_KEY_8] = '8', [MLX_KEY_9] = '9',
	[MLX_KEY_SPACE] = ' ', [MLX_KEY_ENTER] = '\n', [MLX_KEY_DEL] = KEY_DEL,
	[MLX_KEY_BACKSPACE] = KEY_BACKSPACE, [MLX_KEY_ESC] = KEY_ESC,
	[MLX_KEY_UP] = KEY_UP, [MLX_KEY_DOWN] = KEY_DOWN, [MLX_KEY_LEFT] = KEY_LEFT,
	[MLX_KEY_RIGHT] = KEY_RIGHT, [MLX_KEY_SHIFT_LEFT] = KEY_SHIFT_LEFT,
	[MLX_KEY_SHIFT_RIGHT] = KEY_SHIFT_RIGHT, [MLX_KEY_ALT_LEFT] = KEY_ALT_LEFT,
	[MLX_KEY_ALT_RIGHT] = KEY_ALT_RIGHT, [MLX_KEY_CMD_LEFT] = KEY_CMD_LEFT,
	[MLX_KEY_CMD_RIGHT] = KEY_CMD_RIGHT, [MLX_KEY_CTRL] = KEY_CTRL};

	win->event.type = type;
	win->event.key_id = codes[keycode];
	if (type == KEY_PRESS)
		win->event.key[codes[keycode]] = codes[keycode];
	else
		win->event.key[codes[keycode]] = 0;
	return (codes[keycode]);
}

#endif

int	_get_key_press(int keycode, t_win *win)
{
	t_tri_lib	*lib;

	if (!_get_key_event(keycode, win, KEY_PRESS))
		return (0);
	lib = tri_lib();
	lib->event = &win->event;
	_call_user_main(lib);
	return (0);
}

int	_get_key_release(int keycode, t_win *win)
{
	t_tri_lib	*lib;

	if (!_get_key_event(keycode, win, KEY_RELEASE))
		return (0);
	lib = tri_lib();
	lib->event = &win->event;
	_call_user_main(lib);
	return (0);
}
