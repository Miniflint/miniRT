/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:02:41 by herolle           #+#    #+#             */
/*   Updated: 2025/06/14 01:48:32 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"

t_tri_lib	*_init_tri_lib(void)
{
	t_tri_lib			*lib;

	lib = tri_lib();
	if (!lib->_mlx)
	{
		lib->_mlx = mlx_init();
		if (!lib->_mlx)
		{
			lib->_ernum = TRI_INIT_FAILURE;
			return (NULL);
		}
	}
	return (lib);
}
