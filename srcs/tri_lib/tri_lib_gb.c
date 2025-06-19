/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_lib_gb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:19:20 by herolle           #+#    #+#             */
/*   Updated: 2025/06/14 01:34:41 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tri_lib.h"

void	_free_gb(t_tri_lib *lib)
{
	t_list	*tmp;

	while (lib->_gb)
	{
		tmp = lib->_gb;
		lib->_gb = lib->_gb->_next;
		free(tmp->_content);
		free(tmp);
	}
}

void	*tri_malloc(int size)
{
	t_list		*node;
	t_tri_lib	*lib;

	lib = tri_lib();
	node = malloc(sizeof(t_list));
	if (!node)
		return (_set_ernum(lib, TRI_MALLOC_FAILURE));
	node->_content = malloc(size);
	if (!node->_content)
	{
		free(node);
		return (_set_ernum(lib, TRI_MALLOC_FAILURE));
	}
	node->_next = lib->_gb;
	lib->_gb = node;
	return (node);
}

static void	_free_node(t_list *node)
{
	free(node->_content);
	free(node);
}

void	tri_free(void *p)
{
	t_tri_lib	*lib;
	t_list		*cursor;
	t_list		*tmp;

	lib = tri_lib();
	if (!lib->_gb)
		return ;
	cursor = lib->_gb;
	if (lib->_gb->_content == p)
	{
		lib->_gb = lib->_gb->_next;
		return (_free_node(cursor));
	}
	while (cursor)
	{
		tmp = cursor->_next;
		if (tmp && tmp->_content == p)
		{
			cursor->_next = tmp->_next;
			return (_free_node(tmp));
		}
		cursor = cursor->_next;
	}
}
