/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 02:46:10 by hermesrolle       #+#    #+#             */
/*   Updated: 2025/09/07 02:46:11 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"
#include <stdio.h>

void	_get_end_func(int (*f)(void *))
{
	tri_lib()->_user_end = f;
}

void	_quit(void)
{
	t_tri_lib	*lib;
	int			code;

	code = 0;
	lib = tri_lib();
	if (lib->_user_end)
		code = lib->_user_end(lib->_user_content);
	lib->destroy();
	if (code)
		exit(code);
	exit(lib->_ernum);
}
