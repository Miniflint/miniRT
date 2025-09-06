#ifndef TRI_MLX_CODE_H
# define TRI_MLX_CODE_H

# ifdef __linux__

#  define MLX_KEY_PRESS_HOOK 2
#  define MLX_KEY_RELEASE_HOOK 3
#  define MLX_MOUSE_PRESS_HOOK 4
#  define MLX_MOUSE_RELEASE_HOOK 5
#  define MLX_MOUSE_MOVE_HOOK 6
#  define MLX_MOUSE_LEFT 1
#  define MLX_MOUSE_RIGHT 2

#  define MLX_KEY_A 'a'
#  define MLX_KEY_B 'b'
#  define MLX_KEY_C 'c'
#  define MLX_KEY_D 'd'
#  define MLX_KEY_E 'e'
#  define MLX_KEY_F 'f'
#  define MLX_KEY_G 'g'
#  define MLX_KEY_H 'h'
#  define MLX_KEY_I 'i'
#  define MLX_KEY_J 'j'
#  define MLX_KEY_K 'k'
#  define MLX_KEY_L 'l'
#  define MLX_KEY_M 'm'
#  define MLX_KEY_N 'n'
#  define MLX_KEY_O 'o'
#  define MLX_KEY_P 'p'
#  define MLX_KEY_Q 'q'
#  define MLX_KEY_R 'r'
#  define MLX_KEY_S 's'
#  define MLX_KEY_T 't'
#  define MLX_KEY_U 'u'
#  define MLX_KEY_V 'v'
#  define MLX_KEY_W 'w'
#  define MLX_KEY_X 'x'
#  define MLX_KEY_Y 'y'
#  define MLX_KEY_Z 'z'

#  define MLX_KEY_0 '0'
#  define MLX_KEY_1 '1'
#  define MLX_KEY_2 '2'
#  define MLX_KEY_3 '3'
#  define MLX_KEY_4 '4'
#  define MLX_KEY_5 '5'
#  define MLX_KEY_6 '6'
#  define MLX_KEY_7 '7'
#  define MLX_KEY_8 '8'
#  define MLX_KEY_9 '9'

#  define MLX_KEY_SPACE ' '
#  define MLX_KEY_ENTER '\n'
#  define MLX_KEY_BACKSPACE 127

#  define MLX_KEY_ESC 65307
#  define MLX_KEY_SHIFT_LEFT 65505
#  define MLX_KEY_SHIFT_RIGHT 65293
#  define MLX_KEY_ALT_LEFT 261
#  define MLX_KEY_ALT_RIGHT 262
#  define MLX_KEY_CMD_LEFT 259
#  define MLX_KEY_CMD_RIGHT 260
#  define MLX_KEY_CTRL 65507
#  define MLX_KEY_LEFT 65361
#  define MLX_KEY_RIGHT 65363
#  define MLX_KEY_UP 65362
#  define MLX_KEY_DOWN 65364
#  define MLX_MAX_CODE 263
#  define MLX_KEY_DEL 200 // indéfini

# else

#  define MLX_KEY_PRESS_HOOK 2
#  define MLX_KEY_RELEASE_HOOK 3
#  define MLX_MOUSE_PRESS_HOOK 4
#  define MLX_MOUSE_RELEASE_HOOK 5
#  define MLX_MOUSE_MOVE_HOOK 6
#  define MLX_MOUSE_LEFT 1
#  define MLX_MOUSE_RIGHT 2
#  define MLX_KEY_A 0
#  define MLX_KEY_B 11
#  define MLX_KEY_C 8
#  define MLX_KEY_D 2
#  define MLX_KEY_E 14
#  define MLX_KEY_F 3
#  define MLX_KEY_G 5
#  define MLX_KEY_H 4
#  define MLX_KEY_I 34
#  define MLX_KEY_J 38
#  define MLX_KEY_K 40
#  define MLX_KEY_L 37
#  define MLX_KEY_M 46
#  define MLX_KEY_N 45
#  define MLX_KEY_O 31
#  define MLX_KEY_P 35
#  define MLX_KEY_Q 12
#  define MLX_KEY_R 15
#  define MLX_KEY_S 1
#  define MLX_KEY_T 17
#  define MLX_KEY_U 32
#  define MLX_KEY_V 9
#  define MLX_KEY_W 13
#  define MLX_KEY_X 7
#  define MLX_KEY_Y 16
#  define MLX_KEY_Z 6
#  define MLX_KEY_0 29
#  define MLX_KEY_1 18
#  define MLX_KEY_2 19
#  define MLX_KEY_3 20
#  define MLX_KEY_4 21
#  define MLX_KEY_5 23
#  define MLX_KEY_6 22
#  define MLX_KEY_7 26
#  define MLX_KEY_8 28
#  define MLX_KEY_9 25
#  define MLX_KEY_ESC 53
#  define MLX_KEY_SHIFT_LEFT 257
#  define MLX_KEY_SHIFT_RIGHT 258
#  define MLX_KEY_ALT_LEFT 261
#  define MLX_KEY_ALT_RIGHT 262
#  define MLX_KEY_CMD_LEFT 259
#  define MLX_KEY_CMD_RIGHT 260
#  define MLX_KEY_CTRL 256
#  define MLX_KEY_LEFT 123
#  define MLX_KEY_RIGHT 124
#  define MLX_KEY_UP 126
#  define MLX_KEY_DOWN 125
#  define MLX_KEY_ENTER 36
#  define MLX_KEY_SPACE 49
#  define MLX_KEY_BACKSPACE 51
#  define MLX_MAX_CODE 263
#  define MLX_KEY_DEL 200 //indéfini

# endif
#endif