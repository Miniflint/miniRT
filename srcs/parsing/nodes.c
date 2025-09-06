/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:05:32 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:06:19 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	*create_empty_node(size_t size)
{
	void	*new_struct;

	new_struct = malloc(size);
	if (!new_struct)
		return (NULL);
	ft_memset(new_struct, 0, size);
	return (new_struct);
}
