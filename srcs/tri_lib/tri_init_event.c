#include "tri_lib.h"

void	_init_key_event(unsigned char key[KEY_CTRL])
{
	unsigned int	i;

	i = 0;
	while (i < KEY_CTRL)
		key[i++] = 0;
}

void	_init_mouse_event(t_mouse_event *mouse)
{
	mouse->left_press = 0;
	mouse->right_press = 0;
	mouse->left_release = 0;
	mouse->right_release = 0;
	mouse->x = 0;
	mouse->y = 0;
}

void	_init_win_event(t_win_event *win)
{
	win->cross = 0;
}

void	_init_event(t_event *event, t_win *win)
{
	event->type = LOOP;
	event->win_id = win;
	event->key_id = 0;
	_init_key_event(event->key);
	_init_mouse_event(&event->mouse);
	_init_win_event(&event->window);
}