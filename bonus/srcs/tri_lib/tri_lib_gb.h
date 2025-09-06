/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_lib_gb.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermesrolle <hermesrolle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:20:17 by herolle           #+#    #+#             */
/*   Updated: 2025/06/14 01:18:31 by hermesrolle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRI_LIB_GB_H
# define TRI_LIB_GB_H

typedef struct s_list
{
	void			*_content;
	struct s_list	*_next;
}					t_list;

typedef struct s_tri_lib	t_tri_lib;

void	_free_gb(t_tri_lib *lib);
void	*tri_malloc(int size);
void	tri_free(void *p);

#endif