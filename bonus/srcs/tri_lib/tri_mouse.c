#include "tri_lib.h"
#include "tri_mlx_code.h"

int	_get_mouse_press(int button, int x, int y, t_win *win)
{
	t_tri_lib	*lib;

	lib = tri_lib();
	lib->event = &win->event;
	lib->event->mouse.x = x;
	lib->event->mouse.y = y;
	if (button == MLX_MOUSE_RIGHT)
	{
		lib->event->mouse.right = 1;
		lib->event->type = MOUSE_RIGHT_PRESS;
	}
	else if (button == MLX_MOUSE_LEFT)
	{
		lib->event->mouse.left = 1;
		lib->event->type = MOUSE_LEFT_PRESS;
	}
	_call_user_main(lib);
	return (0);
}

int	_get_mouse_release(int button, int x, int y, t_win *win)
{
	t_tri_lib	*lib;

	lib = tri_lib();
	lib->event = &win->event;
	lib->event->mouse.x = x;
	lib->event->mouse.y = y;
	if (button == MLX_MOUSE_RIGHT)
	{
		lib->event->mouse.right = 0;
		lib->event->type = MOUSE_RIGHT_RELEASE;
	}
	else if (button == MLX_MOUSE_LEFT)
	{
		lib->event->mouse.left = 0;
		lib->event->type = MOUSE_LEFT_RELEASE;
	}
	_call_user_main(lib);
	return (0);
}

int	_get_mouse_move(int x, int y, t_win *win)
{
	t_tri_lib	*lib;

	lib = tri_lib();
	lib->event = &win->event;
	lib->event->mouse.x = x;
	lib->event->mouse.y = y;
	lib->event->type = MOUSE_MOVE;
	_call_user_main(lib);
	return (0);
}
