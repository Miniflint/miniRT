/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 02:44:52 by hermesrolle       #+#    #+#             */
/*   Updated: 2025/09/07 02:44:54 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"

void	_tri_putstr(int fd, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	i = write(fd, s, i);
}

int	_print_error(int code)
{
	if (code < TRI_SUCCESS || code >= TRI_UNDEFINED_ERROR)
		_tri_putstr(1, tri_lib()->_error_msg[TRI_UNDEFINED_ERROR]);
	else
		_tri_putstr(1, tri_lib()->_error_msg[code]);
	return (code);
}

const char	*_get_error_message(void)
{
	return (tri_lib()->_error_msg[tri_lib()->_ernum]);
}

void	*_set_ernum(t_tri_lib *lib, int code)
{
	lib->_ernum = code;
	return (NULL);
}
