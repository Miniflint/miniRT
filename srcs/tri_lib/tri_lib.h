/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_lib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 03:38:29 by hermesrolle       #+#    #+#             */
/*   Updated: 2025/06/15 22:26:01 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRI_LIB_H
# define TRI_LIB_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "mlx.h"
# include "tri_lib_gb.h"
# include "tri_colors.h"
# define BACKGROUND_COLOR 0x00000000

typedef struct s_tri_lib	t_tri_lib;

enum
{
	TRI_SUCCESS,
	TRI_FAILURE,
	TRI_UNITIALISED,
	TRI_EXIT_SUCCESS,
	TRI_MALLOC_FAILURE,
	TRI_CREATE_WINDOW_FAILURE,
	TRI_CREATE_RENDER_FAILURE,
	TRI_INVALID_VALUE,
	TRI_INIT_FAILURE,
	TRI_UNDEFINED_ERROR,
	TRI_N_ERROR
};

typedef struct s_win		t_win;

typedef struct s_render
{
	unsigned int	*_data;
	int				_width;
	int				_height;
	int				_size;
	unsigned int	(*_mix_colors)(t_argb top, t_argb base);
	t_win			*_parent_win;
	struct s_render	*_next;
}					t_render;

typedef struct s_img
{
	void			*_img;
	void			*_data;
	int				_bpp;
	int				_size_line;
	int				_width;
	int				_endian;
	struct s_img	*_next;
}					t_img;

typedef struct s_img_render
{
	t_img		_img;
	t_render	_render;
}				t_img_render;

struct s_win
{
	void			*_win;
	int				_width;
	int				_height;
	char			*_name;
	t_img_render	_base_render;
	t_render		*_renders;
	t_render		*_last_render;
	struct s_win	*_next;
};

struct s_tri_lib
{
	t_tri_lib		*(*init)(void);
	void			(*destroy)(void);
	t_win			*(*create_window)(char *name, int width, int height);
	void			(*refresh)(t_win *win);
	t_img			*(*open_img)(char *path);
	int				(*loop)(int	(*f)(t_tri_lib *, void *), void *content);
	void			(*delay)(int fps);
	t_render		*(*create_render)(t_win *win);
	const char		*(*get_error_msg)(void);
	void			(*destroy_window)(t_win *win);
	void			(*destroy_render)(t_render *render);
	int				(*print_error)(int code);
	unsigned int	(*get_pixel)(t_render *render, int x, int y);
	void			(*put_pixel_to_render)(t_render *render, t_argb color, int x, int y);
	void			(*replace_pixel_on_render)(t_render *render,
						unsigned int color, int x, int y);
	void			(*put_pixel_to_window)(t_win *win, t_argb color, int x, int y);
	void			(*replace_pixel_on_window)(t_win *win, unsigned int color, int x, int y);
	void			(*erase_fill_render)(t_render *render, unsigned int color);
	void			(*fill_render)(t_render *render, t_argb color);
	void			(*erase_render)(t_render *render);
	void			(*erase_window)(t_win *win);
	void			(*erase_windows)(void);
	void			(*draw_window)(t_win *win);
	void			(*draw_windows)(void);
	void			(*change_background)(unsigned int	color);
	t_win			*_windows;
	t_img			*_imgs;
	const char		*_error_msg[TRI_N_ERROR];
	int				_ernum;
	void			*_mlx;
	unsigned int	_bg_color;
	t_list			*_gb;
};

/*---------------------TRI_CREATE_RENDER----------------------*/

t_render			*_create_render(t_win *win);
int					_create_base_render(t_win *win);

/*---------------------TRI_CREATE_WINDOW----------------------*/

t_win				*_create_window(char *name, int width, int height);

/*---------------------TRI_DESTROY_RENDER---------------------*/

void				_destroy_render(t_render *render);
void				_destroy_base_render(t_img_render *render);

/*---------------------TRI_DESTROY_WINDOW---------------------*/

void				_destroy_window(t_win *win);

/*------------------------TRI_DESTROY-------------------------*/

void				_free_renders(t_render *renders);
void				_tri_destroy_imgs(t_tri_lib *lib);
void				_tri_destroy_windows(t_tri_lib *lib);
void				_destroy_tri_lib(void);

/*-------------------------TRI_ERROR--------------------------*/

void				*_set_ernum(t_tri_lib *lib, int code);
void				_tri_putstr(int fd, const char *s);
int					_print_error(int code);
const char			*_get_error_message(void);

/*--------------------------TRI_INIT--------------------------*/

t_tri_lib			*_init_tri_lib(void);

/*--------------------------TRI_LIB---------------------------*/

t_img				*_open_img(char *path);
void				_close_window_hook(t_tri_lib *lib);
void				_refresh_window(t_win *win);
t_tri_lib			*tri_lib(void);

/*--------------------------TRI_LOOP--------------------------*/

int					_main_loop(int (*f)(t_tri_lib *, void *), void *content);
void				_delay(int fps);

/*-----------------------TRI_PUT_PIXEL------------------------*/

unsigned int		_get_pixel(t_render *render, int x, int y);
void				_put_pixel_to_render(t_render *render, t_argb color, int x, int y);
void				_replace_pixel_on_render(t_render *render,
						unsigned int color, int x, int y);
void				_put_pixel_to_window(t_win *win, t_argb color, int x, int y);
void				_replace_pixel_on_window(t_win *win, unsigned int color, int x, int y);
void				_erase_fill_render(t_render *render, unsigned int color);
void				_fill_render(t_render *render, t_argb color);
void				_erase_render(t_render *render);
void				_erase_window(t_win *win);
void				_erase_windows(void);
void				_draw_render_to_render(t_render *top, t_render *base);
void				_draw_window(t_win *win);
void				_draw_windows(void);
void				_change_background(unsigned int	color);

#endif