/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __fake_globals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgoel <trgoel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 21:05:15 by trgoel            #+#    #+#             */
/*   Updated: 2025/09/06 21:05:19 by trgoel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_all	*__get_all(void)
{
	static t_all	rtn_all;

	return (&rtn_all);
}

t_object	*__get_head(t_object *curr_head)
{
	static t_object	*curr;

	if (curr_head)
		curr = curr_head;
	return (curr);
}
