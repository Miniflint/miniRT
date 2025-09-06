#ifndef TRI_GET_KEY_H
# define TRI_GET_KEY_H
# include "tri_lib.h"
# include "tri_mlx_code.h"

# ifdef __linux__

void			_special_key_set(int keycode, unsigned char *key);
unsigned char	_set_key(int keycode, t_win *win,
					t_event_type type, const unsigned char codes[MLX_MAX_CODE]);
unsigned char	_get_key_event(int keycode, t_win *win,
					t_event_type type);

# else

unsigned char	_get_key_event(int keycode, t_win *win,
					t_event_type type);

# endif

#endif