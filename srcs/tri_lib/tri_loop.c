/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:28:01 by herolle           #+#    #+#             */
/*   Updated: 2025/06/14 04:05:26 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"

void	_delay(int fps)
{
	(void)fps;
	return ;
}

int	_main_loop(int (*f)(t_tri_lib *, void *), void *content)
{
	t_tri_lib	*lib;
	int			ret_code;

	lib = tri_lib();
	if (!lib->_mlx)
		return (TRI_UNITIALISED);
	ret_code = f(lib, content);
	if (ret_code)
		return (ret_code);
	_close_window_hook(lib);
	mlx_loop(lib->_mlx);
	return (TRI_SUCCESS);
}
