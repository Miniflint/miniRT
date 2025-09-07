/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_get_key_event.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 03:34:21 by hermesrolle       #+#    #+#             */
/*   Updated: 2025/09/07 02:45:05 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_get_key.h"

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
