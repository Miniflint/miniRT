#include "tri_lib.h"
#include "tri_mlx_code.h"

int	_get_mouse_press(int button, int x, int y, t_win *win)
{
	t_tri_lib	*lib;

	// printf("Mouse press event: [button = %d], [x = %d, y = %d]\n", button, x, y);
	lib = tri_lib();
	lib->event = &win->event;
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
	lib->_user_main(lib, lib->_user_content);
	return (0);
}

int	_get_mouse_release(int button, int x, int y, t_win *win)
{
	t_tri_lib	*lib;

	// printf("Mouse release event: [button = %d], [x = %d, y = %d]\n", button, x, y);
	lib = tri_lib();
	lib->event = &win->event;
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
	lib->_user_main(lib, lib->_user_content);
	return (0);
}

int	_get_mouse_move(int x, int y, t_win *win)
{
	t_tri_lib	*lib;

	// printf("Mouse move event: [x = %d, y = %d]\n", x, y);
	lib = tri_lib();
	lib->event = &win->event;
	lib->event->mouse.x = x;
	lib->event->mouse.y = y;
	lib->event->type = MOUSE_MOVE;
	lib->_user_main(lib, lib->_user_content);
	return (0);
}
