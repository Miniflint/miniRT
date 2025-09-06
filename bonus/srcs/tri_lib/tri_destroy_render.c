/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_destroy_render.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:53:36 by herolle           #+#    #+#             */
/*   Updated: 2025/06/15 20:32:39 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"

void	_destroy_render(t_render *render)
{
	t_render		*cursor;
	t_render		*tmp;

	if (!render)
		return ;
	cursor = render->_parent_win->_renders;
	if (cursor == render)
	{
		render->_parent_win->_renders = render->_parent_win->_renders->_next;
		free(cursor->_data);
		free(cursor);
	}
	while (cursor->_next && cursor->_next != render)
		cursor = cursor->_next;
	if (!cursor->_next)
		return ;
	tmp = cursor->_next;
	cursor->_next = tmp->_next;
	free(tmp->_data);
	free(tmp);
}

void	_destroy_base_render(t_img_render *render)
{
	if (render->_img._img)
		mlx_destroy_image(tri_lib()->_mlx, render->_img._img);
	render->_img._img = NULL;
}
