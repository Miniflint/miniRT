/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:07:31 by herolle           #+#    #+#             */
/*   Updated: 2025/06/15 20:55:30 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"

void	_free_renders(t_render *renders)
{
	t_render	*tmp;

	while (renders)
	{
		tmp = renders;
		if (tmp->_data)
			free(tmp->_data);
		renders = renders->_next;
		free(tmp);
	}
}

void	_tri_destroy_imgs(t_tri_lib *lib)
{
	t_img	*imgs;
	t_img	*tmp;

	imgs = lib->_imgs;
	while (imgs)
	{
		tmp = imgs;
		imgs = imgs->_next;
		mlx_destroy_image(lib->_mlx, tmp->_img);
		free(tmp);
	}
	lib->_imgs = NULL;
}

void	_tri_destroy_windows(t_tri_lib *lib)
{
	t_win	*windows;
	t_win	*tmp;

	windows = lib->_windows;
	while (windows)
	{
		tmp = windows;
		windows = windows->_next;
		mlx_destroy_window(lib->_mlx, tmp->_win);
		if (tmp->_renders)
			_free_renders(tmp->_renders);
		free(tmp);
		tmp = NULL;
	}
	lib->_windows = NULL;
}

#ifdef __linux__

void	_destroy_tri_lib(void)
{
	t_tri_lib	*lib;

	printf("Linux destroy\n");
	lib = tri_lib();
	if (lib->_imgs)
		_tri_destroy_imgs(lib);
	if (lib->_windows)
		_tri_destroy_windows(lib);
	if (lib->_mlx)
	{
		mlx_destroy_display(lib->_mlx);
		free(lib->_mlx);
		lib->_mlx = NULL;
	}
	if (lib->_gb)
		_free_gb(lib);
	return ;
}

#else

void	_destroy_tri_lib(void)
{
	t_tri_lib	*lib;

	lib = tri_lib();
	if (lib->_imgs)
		_tri_destroy_imgs(lib);
	if (lib->_windows)
		_tri_destroy_windows(lib);
	if (lib->_mlx)
	{
		free(lib->_mlx);
		lib->_mlx = NULL;
	}
	if (lib->_gb)
		_free_gb(lib);
	return ;
}

#endif
